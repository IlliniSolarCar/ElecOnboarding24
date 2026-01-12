#ifndef COMMON_API_DMACONTROLLER_H_
#define COMMON_API_DMACONTROLLER_H_

#include "mbed.h"

const uint8_t kNumDmaChannels = 18;

/**
 * Singleton DMA controller class, shared between multiple DMA peripherals.
 *
 * Warning: NOT MEANT TO BE A STABLE, CROSS-DEVICE API. Treat this class as a device-specific
 * implementation details used to share common DMA tasks.
 */
class DmaController {
public:
  static DmaController& get() {
    static DmaController instance;
    return instance;
  }

  /**
   * Initiates a memory-to-peripheral transfer, where the source address
   * increments but the destination does not.
   * If callback is not NULL, the callback is fired on transfer completion.
   *
   * @param dst destination pointer, non-incrementing
   * @param src source pointer, incrementing
   * @param len transfer length, in bytes
   * @param channel DMA channel to use, which can dictate things like request source
   *
   * TODO: channel is a hack for peripheral-specific constraints, needs a more
   * general API.
   */
  void memToPeriphTransfer(volatile void* dst, void* src, size_t len,
      uint8_t channel, void (*callback)() = NULL);

  // Version with class member callback
  template<typename T>
  void memToPeriphTransfer(volatile void* dst, void* src, size_t len,
        uint8_t channel, T* tptr, void (T::*mptr)(void)) {
    dmaCallbacks_[channel].attach(tptr, mptr);
    memToPeriphTransfer(dst, src, len, channel, true);
  }

protected:
  DmaController();

  void memToPeriphTransfer(volatile void* dst, void* src, size_t len,
      uint8_t channel, bool interrupt);

  static void irqHandler();

  static uint32_t dmaDescriptors_[kNumDmaChannels][4];
  static FunctionPointer dmaCallbacks_[kNumDmaChannels];
};

#endif
