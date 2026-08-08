#include "fft.h"

#include <cmath>

// NOTE: Reference implementation stub. In the actual firmware build,
// replace the body of computeMagnitudeSpectrum with a call into the
// arduinoFFT library (or ESP-DSP's dsps_fft2r_fc32). This stub performs
// an O(n^2) DFT magnitude computation — correct but slower than radix-2
// FFT, acceptable for FFT_SIZE <= 256 during development/testing.

namespace FFTProcessor {

void computeMagnitudeSpectrum(float* real, float* imag, int length,
                               float /*sampleRateHz*/, float* magnitudeOut) {
  for (int k = 0; k < length / 2; k++) {
    float sumReal = 0.0f;
    float sumImag = 0.0f;
    for (int n = 0; n < length; n++) {
      float angle = -2.0f * (float)M_PI * k * n / length;
      sumReal += real[n] * cosf(angle) - imag[n] * sinf(angle);
      sumImag += real[n] * sinf(angle) + imag[n] * cosf(angle);
    }
    magnitudeOut[k] = sqrtf(sumReal * sumReal + sumImag * sumImag);
  }
}

float dominantFrequency(const float* magnitudeSpectrum, int halfLength,
                         float sampleRateHz, int fftLength) {
  int peakBin = 1;
  float peakVal = magnitudeSpectrum[1];
  for (int i = 2; i < halfLength; i++) {
    if (magnitudeSpectrum[i] > peakVal) {
      peakVal = magnitudeSpectrum[i];
      peakBin = i;
    }
  }
  return (peakBin * sampleRateHz) / (float)fftLength;
}

}  // namespace FFTProcessor
