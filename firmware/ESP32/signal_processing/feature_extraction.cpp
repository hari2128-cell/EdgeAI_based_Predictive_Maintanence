#include "feature_extraction.h"

#include <cmath>

#include "fft.h"

namespace FeatureExtraction {

static float computeRMS(const float* signal, int length) {
  float sumSq = 0.0f;
  for (int i = 0; i < length; i++) sumSq += signal[i] * signal[i];
  return sqrtf(sumSq / length);
}

static float computePeak(const float* signal, int length) {
  float peak = 0.0f;
  for (int i = 0; i < length; i++) {
    float absVal = fabsf(signal[i]);
    if (absVal > peak) peak = absVal;
  }
  return peak;
}

static float computeMean(const float* signal, int length) {
  float sum = 0.0f;
  for (int i = 0; i < length; i++) sum += signal[i];
  return sum / length;
}

static float computeVariance(const float* signal, int length, float mean) {
  float sumSq = 0.0f;
  for (int i = 0; i < length; i++) {
    float d = signal[i] - mean;
    sumSq += d * d;
  }
  return sumSq / length;
}

static float computeBandEnergy(const float* magnitudeSpectrum, int specLength) {
  float energy = 0.0f;
  for (int i = 0; i < specLength; i++) {
    energy += magnitudeSpectrum[i] * magnitudeSpectrum[i];
  }
  return energy;
}

FeatureVector extractVibrationFeatures(const float* timeSignal, int timeLength,
                                        const float* magnitudeSpectrum, int specLength,
                                        float sampleRateHz) {
  FeatureVector fv{};

  float rms = computeRMS(timeSignal, timeLength);
  float peak = computePeak(timeSignal, timeLength);
  float mean = computeMean(timeSignal, timeLength);
  float variance = computeVariance(timeSignal, timeLength, mean);
  float crestFactor = (rms > 1e-6f) ? (peak / rms) : 0.0f;
  float dominantFreq = FFTProcessor::dominantFrequency(magnitudeSpectrum, specLength,
                                                         sampleRateHz, timeLength);
  float bandEnergy = computeBandEnergy(magnitudeSpectrum, specLength);

  fv.values[0] = rms;
  fv.values[1] = peak;
  fv.values[2] = mean;
  fv.values[3] = variance;
  fv.values[4] = crestFactor;
  fv.values[5] = dominantFreq;
  fv.values[6] = bandEnergy;
  fv.values[7] = 0.0f;
  fv.values[8] = 0.0f;
  fv.values[9] = 0.0f;

  return fv;
}

void extractAudioFeatures(const float* timeSignal, int timeLength,
                           const float* magnitudeSpectrum, int specLength,
                           float sampleRateHz, float* audioRmsOut,
                           float* audioPeakOut, float* audioDominantFreqOut) {
  *audioRmsOut = computeRMS(timeSignal, timeLength);
  *audioPeakOut = computePeak(timeSignal, timeLength);
  *audioDominantFreqOut = FFTProcessor::dominantFrequency(magnitudeSpectrum, specLength,
                                                            sampleRateHz, timeLength);
}

}  // namespace FeatureExtraction
