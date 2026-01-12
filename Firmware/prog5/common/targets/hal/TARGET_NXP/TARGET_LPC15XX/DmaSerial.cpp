#include "DmaSerial.h"

DmaSerialBase::DmaSerialBase(PinName tx, PinName rx, int baud, uint8_t* bufferBegin, uint8_t* bufferEnd) :
    RawSerial(tx, rx), bufferBegin_(bufferBegin), bufferEnd_(bufferEnd) {
  // baud appears part of the constructor in newer mbed versions, but we'll
  // fake it here.
  this->baud(baud);
  queueStart_.store(bufferBegin_);
  queueEnd_.store(bufferBegin_);
  dmaRunning_.store(false);
}

int DmaSerialBase::putc(int character) {
  uint8_t* queueEnd = queueEnd_.load(std::memory_order_relaxed);
  uint8_t* queueStart = queueStart_.load(std::memory_order_relaxed);

  if (queueEnd == queueStart - 1
      || (queueStart == bufferBegin_ && queueEnd == bufferEnd_ - 1)) {
    return EOF;
  }
  *queueEnd = (uint8_t)character;
  queueEnd++;
  if (queueEnd >= bufferEnd_) {
    queueEnd = bufferBegin_;
  }
  queueEnd_.store(queueEnd, std::memory_order_relaxed);

  if (!dmaRunning_.load(std::memory_order_acq_rel)) {
    startTransfer();
  }
  return character;
}

int DmaSerialBase::puts(const char* str) {
  size_t len = strlen(str);
  if (put((uint8_t*)str, len)) {
    return 0;
  } else {
    return EOF;
  }
}

bool DmaSerialBase::put(uint8_t* data, size_t len) {
  size_t remaining;
  uint8_t* queueEnd = queueEnd_.load(std::memory_order_relaxed);
  uint8_t* queueStart = queueStart_.load(std::memory_order_relaxed);
  if (queueStart < queueEnd) {  // queue does not wrap around
    remaining = (bufferEnd_ - bufferBegin_) - (queueEnd - queueStart);
  } else if (queueStart > queueEnd ) {  // queue wraps around
    remaining = queueStart - queueEnd;
  } else {  // empty queue
    remaining = bufferEnd_ - bufferBegin_;
  }
  if (remaining < len + 1) {
    return false;
  }

  size_t remainingContinuous = bufferEnd_ - queueEnd;
  size_t transferContinuous = std::min(len, remainingContinuous);
  memcpy(queueEnd, data, transferContinuous);
  len -= transferContinuous;
  if (len > 0) {  // more elements to copy after wrap-around
    data += transferContinuous;
    memcpy(bufferBegin_, data, len);
    queueEnd_.store(bufferBegin_ + len, std::memory_order_relaxed);
  } else {
    queueEnd_.store(queueEnd + transferContinuous, std::memory_order_relaxed);
  }

  if (!dmaRunning_.load(std::memory_order_acq_rel)) {
    startTransfer();
  }
  return true;
}

uint8_t DmaSerialBase::dmaChannel() {
  // Select DMA channel with the request input for this USART
  switch (_serial.index) {
  case 0: return 1;
  case 1: return 3;
  case 2: return 5;
  default: error("Unknown DMA channel for serial"); return 0;
  }
}

void DmaSerialBase::startTransfer() {
  if (dmaRunning_.load(std::memory_order_acquire)) {
    error("DMA transfer already running");
  }

  uint8_t* queueStart = queueStart_.load(std::memory_order_acquire);
  uint8_t* queueEnd = queueEnd_.load(std::memory_order_acquire);

  size_t len;
  if (queueStart < queueEnd) {  // queue does not wrap around
    len = queueEnd - queueStart;
    nextBufferStart_ = queueEnd;
  } else if (queueStart > queueEnd ) {  // queue wraps around
    len = bufferEnd_ - queueStart;
    nextBufferStart_ = bufferBegin_;
  } else {  // empty queue
    error("Empty queue");
  }

  dmaRunning_.store(true, std::memory_order_release);
  DmaController::get().memToPeriphTransfer(
      &(_serial.uart->TXDATA),
      queueStart, len,
      dmaChannel(),
      this, &DmaSerialBase::irqTransferDone);
}

void DmaSerialBase::irqTransferDone() {
  queueStart_.store(nextBufferStart_);

  // Inside interrupt, memory ordering not an issue
  uint8_t* queueStart = queueStart_.load(memory_order_relaxed);
  uint8_t* queueEnd = queueEnd_.load(memory_order_relaxed);

  dmaRunning_.store(false, std::memory_order_relaxed);
  if (queueStart == queueEnd) {  // empty queue
    return;
  } else {
    startTransfer();
  }
}

