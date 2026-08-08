#ifndef INFERENCE_H
#define INFERENCE_H

#include "../signal_processing/feature_extraction.h"

// Thin wrapper around TensorFlow Lite Micro's MicroInterpreter.
namespace Inference {

bool begin();
int classify(const FeatureExtraction::FeatureVector& features, float* outScores);
bool isReady();

}  // namespace Inference

#endif // INFERENCE_H
