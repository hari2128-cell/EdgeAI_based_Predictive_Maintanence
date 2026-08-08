#ifndef HELPERS_H
#define HELPERS_H

#include <cmath>

namespace Helpers {

inline float clampf(float v, float lo, float hi) {
  if (v < lo) return lo;
  if (v > hi) return hi;
  return v;
}

inline int argmax(const float* arr, int n) {
  int best = 0;
  for (int i = 1; i < n; i++) {
    if (arr[i] > arr[best]) best = i;
  }
  return best;
}

}  // namespace Helpers

#endif // HELPERS_H
