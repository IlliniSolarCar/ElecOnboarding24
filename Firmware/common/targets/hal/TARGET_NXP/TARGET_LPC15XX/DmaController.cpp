#include "DmaController.h"

uint32_t DmaController::dmaDescriptors_[18][4] __attribute__((aligned(512)));
FunctionPointer DmaController::dmaCallbacks_[kNumDmaChannels];

void DmaController::memToPeriphTransfer(volatile void* dst, void* src, size_t len,
    uint8_t channel, void (*callback)()) {
  if (callback) {
    dmaCallbacks_[channel].attach(callback);
    memToPeriphTransfer(dst, src, len, channel, true);
  } else {
    memToPeriphTransfer(dst, src, len, channel, false);
  }
}

DmaController::DmaController() {
  // Enable the DMA peripheral
  LPC_SYSCON->SYSAHBCLKCTRL0 |= 1 << 20;  // enable clock for DMA
  LPC_SYSCON->PRESETCTRL0 |= 1 << 20;  // DMA reset
  LPC_SYSCON->PRESETCTRL0 &= ~(1 << 20);  // clear DMA reset

  LPC_DMA->CTRL = 1;
  LPC_DMA->SRAMBASE = (uint32_t)dmaDescriptors_;

  NVIC_SetVector(DMA_IRQn, (uint32_t)&irqHandler);
  NVIC_EnableIRQ(DMA_IRQn);
}

void DmaController::memToPeriphTransfer(volatile void* dst, void* src, size_t len,
    uint8_t channel, bool interrupt) {
  // ensure channel isn't in use
  if (LPC_DMA->ACTIVE0 & (1 << channel)) {
    error("DMA channel already active");
  }
  if (len > 1024) {
    error("DMA transfer length exceeds maximum");
  }

  dmaDescriptors_[channel][0] = 0;
  dmaDescriptors_[channel][1] = (uint32_t)src + len - 1;  // source end address
  dmaDescriptors_[channel][2] = (uint32_t)dst;  // destination end address
  dmaDescriptors_[channel][3] = 0;  // next descriptor

  if (interrupt) {
    LPC_DMA->INTENSET0 = 1 << channel;
  } else {
    LPC_DMA->INTENCLR0 = 1 << channel;
  }

  LPC_DMA->ENABLESET0 = 1 << channel;  // enable channel
  volatile uint32_t* channelCfg = &LPC_DMA->CFG0 + 4 * channel;
  volatile uint32_t* xferCfg = &LPC_DMA->XFERCFG0 + 4 * channel;
  *channelCfg = 1 | (0x7 << 16);
  *xferCfg = 1 | (1 << 2) | (interrupt << 4) | (0x1 << 12) | ((len - 1) << 16);
  LPC_DMA->SETVALID0 = 1 << channel;  // channel valid
}

void DmaController::irqHandler() {
  for (uint8_t i=0; i<kNumDmaChannels; i++) {
    if (LPC_DMA->INTA0 & (1 << i)) {
      LPC_DMA->INTA0 = 1 << i;  // setting bit clears interrupt
      dmaCallbacks_[i]();
    }
  }
}
