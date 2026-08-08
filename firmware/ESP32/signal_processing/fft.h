#ifndef FFT_H
#define FFT_H

// Thin wrapper producing a magnitude spectrum from a windowed real-valued
// input buffer. In production, back this with arduinoFFT or ESP-DSP.
namespace FFTProcessor {

void computeMagnitudeSpectrum(float* real, float* imag, int length,
                               float sampleRateHz, float* magnitudeOut);

float dominantFrequency(const float* magnitudeSpectrum, int halfLength,
                         float sampleRateHz, int fftLength);

}  // namespace FFTProcessor

#endif // FFT_H
