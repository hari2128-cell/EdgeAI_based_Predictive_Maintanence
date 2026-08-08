#ifndef FEATURE_EXTRACTION_H
#define FEATURE_EXTRACTION_H

// Extracts the fixed-length feature vector consumed by the TinyML model.
// Layout (must match tinyml/Feature_Extraction/extract_features.py):
//   [0] vibration_rms          [5] vibration_dominant_frequency
//   [1] vibration_peak          [6] vibration_band_energy
//   [2] vibration_mean           [7] audio_rms
//   [3] vibration_variance        [8] audio_peak
//   [4] vibration_crest_factor     [9] audio_dominant_frequency
namespace FeatureExtraction {

struct FeatureVector {
  float values[10];
};

FeatureVector extractVibrationFeatures(const float* timeSignal, int timeLength,
                                        const float* magnitudeSpectrum, int specLength,
                                        float sampleRateHz);

void extractAudioFeatures(const float* timeSignal, int timeLength,
                           const float* magnitudeSpectrum, int specLength,
                           float sampleRateHz, float* audioRmsOut,
                           float* audioPeakOut, float* audioDominantFreqOut);

}  // namespace FeatureExtraction

#endif // FEATURE_EXTRACTION_H
