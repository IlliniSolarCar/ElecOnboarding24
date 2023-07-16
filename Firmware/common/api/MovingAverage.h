#ifndef COMMON_API_MOVINGAVERAGE_H_
#define COMMON_API_MOVINGAVERAGE_H_

/**
 * Moving average filter with constant-time updating (running sum).
 *
 * @tparam T type of individual data
 * @tparam V type of sum, which can be larger for accumulation
 * @tparam L number of samples to average over, for array sizing
 */
template <typename T, typename V, size_t L>
class MovingAverage {
public:
  MovingAverage() :
    bufferPos_(buffer_), bufferEnd_(buffer_ + L),
    numSamples_(0), sum_(0) {
  }

  /**
   * Adds a new sample to the moving average filter
   */
  void update(T sample) {
    if (numSamples_ >= L) {
      if (bufferPos_ >= bufferEnd_) {
        bufferPos_ = buffer_;
      }
      sum_ -= *bufferPos_;
      sum_ += sample;
      *bufferPos_ = sample;
      bufferPos_++;
    } else {
      sum_ += sample;
      *bufferPos_ = sample;
      bufferPos_++;
      numSamples_ += 1;
    }
  }

  /**
   * Returns the average
   */
  T read() const {
    if (numSamples_ >= L) {
      return (sum_ + L / 2) / L;  // rounding divide
    } else {
      return (sum_ + numSamples_ / 2) / numSamples_;  // rounding divide
    }
  }

  /**
   * Resets the moving average filter.
   */
  void reset() {
    numSamples_ = 0;
    bufferPos_ = buffer_;
    sum_ = 0;
  }

protected:
  T buffer_[L];
  T* bufferPos_;  // pointer to next element to write to
  const T* bufferEnd_;  // pointer to one past end of buffer

  size_t numSamples_;
  V sum_;
};

#endif //COMMON_API_MOVINGAVERAGE_H_
