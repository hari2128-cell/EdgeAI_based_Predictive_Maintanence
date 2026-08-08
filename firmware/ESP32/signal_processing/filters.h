#ifndef FILTERS_H
#define FILTERS_H

// Lightweight, allocation-free signal filters: DC removal, moving-average.
namespace Filters {

class DCRemover {
 public:
  explicit DCRemover(float alpha) : alpha_(alpha), dcEstimate_(0.0f), initialized_(false) {}

  float process(float sample) {
    if (!initialized_) {
      dcEstimate_ = sample;
      initialized_ = true;
    } else {
      dcEstimate_ = alpha_ * dcEstimate_ + (1.0f - alpha_) * sample;
    }
    return sample - dcEstimate_;
  }

 private:
  float alpha_;
  float dcEstimate_;
  bool initialized_;
};

template <int WindowSize>
class MovingAverage {
 public:
  MovingAverage() : index_(0), count_(0), sum_(0.0f) {
    for (int i = 0; i < WindowSize; i++) buffer_[i] = 0.0f;
  }

  float process(float sample) {
    sum_ -= buffer_[index_];
    buffer_[index_] = sample;
    sum_ += sample;
    index_ = (index_ + 1) % WindowSize;
    if (count_ < WindowSize) count_++;
    return sum_ / count_;
  }

 private:
  float buffer_[WindowSize];
  int index_;
  int count_;
  float sum_;
};

}  // namespace Filters

#endif // FILTERS_H
