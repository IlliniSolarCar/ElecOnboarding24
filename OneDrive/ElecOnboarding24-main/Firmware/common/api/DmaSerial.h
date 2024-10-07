#ifndef COMMON_API_DMASERIAL_H_
#define COMMON_API_DMASERIAL_H_

#include "mbed.h"
#include <algorithm>
#include <atomic>

#include "DmaController.h"

/**
 * Serial with DMA support, using a lock-free single-producer single-consumer circular queue.
 * DMA support  is implemented for transmit only, receive is still polling.
 */
class DmaSerialBase : public RawSerial {
public:
  DmaSerialBase(PinName tx, PinName rx, int baud, uint8_t* bufferBegin, uint8_t* bufferEnd);

  int putc(int character);
  int puts(const char* str);
  bool put(uint8_t* data, size_t len);

protected:
  uint8_t* const bufferBegin_;
  uint8_t* const bufferEnd_;

  // Invariant: at least one element in buffer always left empty
  // buffer is empty when bufferStart_ == bufferEnd_
  // Atomics are used to prevent re-ordering of certain loads and stores, to correctly implement
  // the lock-free queue even across threads and interrupts.
  atomic<uint8_t*> queueStart_;  // pointer to first buffer element
  atomic<uint8_t*> queueEnd_;  // pointer to the next buffer element to be written
  uint8_t* nextBufferStart_;  // queueStart_ becomes this after a DMA transfer completes
  atomic<bool> dmaRunning_;

  uint8_t dmaChannel();
  void startTransfer();
  void irqTransferDone();
};

template <size_t N>
class DmaSerial : public DmaSerialBase {
public:
  DmaSerial(PinName tx, PinName rx, int baud) :
    DmaSerialBase(tx, rx, baud, buffer_, buffer_ + N) {
  }

protected:
  uint8_t buffer_[N];
};

#endif
