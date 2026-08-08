#ifndef NORMALIZATION_H
#define NORMALIZATION_H

namespace Normalization {

// Min-max normalize a buffer in place to the [-1, 1] range.
inline void minMaxNormalize(float* buffer, int length) {
  float minVal = buffer[0];
  float maxVal = buffer[0];
  for (int i = 1; i < length; i++) {
    if (buffer[i] < minVal) minVal = buffer[i];
    if (buffer[i] > maxVal) maxVal = buffer[i];
  }
  float range = maxVal - minVal;
  if (range < 1e-6f) range = 1e-6f;
  for (int i = 0; i < length; i++) {
    buffer[i] = 2.0f * ((buffer[i] - minVal) / range) - 1.0f;
  }
}

}  // namespace Normalization

#endif // NORMALIZATION_H
