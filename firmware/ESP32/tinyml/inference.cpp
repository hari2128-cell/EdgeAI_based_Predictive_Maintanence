#include "inference.h"

#include "../app_config.h"
#include "../utils/helpers.h"
#include "../utils/logger.h"
#include "labels.h"
#include "model_data.h"

// NOTE: This file sketches the TensorFlow Lite Micro integration. Uncomment
// the TFLite Micro includes below and the commented interpreter setup after
// adding the TensorFlowLite_ESP32 library to your project.
// #include <tensorflow/lite/micro/all_ops_resolver.h>
// #include <tensorflow/lite/micro/micro_error_reporter.h>
// #include <tensorflow/lite/micro/micro_interpreter.h>
// #include <tensorflow/lite/schema/schema_generated.h>

namespace Inference {

namespace {
bool ready_ = false;
uint8_t tensorArena[TENSOR_ARENA_SIZE];
}  // namespace

bool begin() {
  if (g_model_len == 0) {
    Logger::warn("Inference", "No model present (model_data.h is a placeholder). "
                               "Falling back to threshold-based classification.");
    ready_ = false;
    return false;
  }

  // --- Real TFLite Micro setup (uncomment once library + model are in place) ---
  // static tflite::MicroErrorReporter micro_error_reporter;
  // const tflite::Model* model = tflite::GetModel(g_model);
  // static tflite::AllOpsResolver resolver;
  // static tflite::MicroInterpreter static_interpreter(
  //     model, resolver, tensorArena, TENSOR_ARENA_SIZE, &micro_error_reporter);
  // if (static_interpreter.AllocateTensors() != kTfLiteOk) {
  //   Logger::error("Inference", "AllocateTensors() failed");
  //   return false;
  // }

  ready_ = true;
  Logger::info("Inference", "TensorFlow Lite Micro interpreter ready");
  return ready_;
}

int classify(const FeatureExtraction::FeatureVector& features, float* outScores) {
  if (!ready_) {
    // Fallback: threshold classifier on vibration RMS, keeping the
    // end-to-end pipeline testable before a trained model is deployed.
    float rms = features.values[0];
    int predicted;
    if (rms >= VIBRATION_FAULT_THRESHOLD) {
      predicted = 2;
    } else if (rms >= VIBRATION_WARNING_THRESHOLD) {
      predicted = 1;
    } else {
      predicted = 0;
    }
    for (int i = 0; i < kNumClasses; i++) outScores[i] = (i == predicted) ? 1.0f : 0.0f;
    return predicted;
  }

  // --- Real inference (uncomment once interpreter is wired up) ---
  // TfLiteTensor* input = static_interpreter.input(0);
  // for (int i = 0; i < FEATURE_VECTOR_SIZE; i++) input->data.f[i] = features.values[i];
  // if (static_interpreter.Invoke() != kTfLiteOk) {
  //   Logger::error("Inference", "Invoke() failed");
  //   return -1;
  // }
  // TfLiteTensor* output = static_interpreter.output(0);
  // for (int i = 0; i < kNumClasses; i++) outScores[i] = output->data.f[i];
  // return Helpers::argmax(outScores, kNumClasses);

  return -1;
}

bool isReady() { return ready_; }

}  // namespace Inference
