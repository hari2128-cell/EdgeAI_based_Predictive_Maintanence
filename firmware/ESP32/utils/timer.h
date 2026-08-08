#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

// Simple non-blocking interval timer, avoids delay()-based blocking loops.
class IntervalTimer {
 public:
  explicit IntervalTimer(unsigned long intervalMs) : interval_(intervalMs), last_(0) {}

  bool ready() {
    unsigned long now = millis();
    if (now - last_ >= interval_) {
      last_ = now;
      return true;
    }
    return false;
  }

 private:
  unsigned long interval_;
  unsigned long last_;
};

#endif // TIMER_H
