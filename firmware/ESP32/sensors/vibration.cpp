#include "vibration.h"

#include <Arduino.h>
#include <Wire.h>

#include "../app_config.h"
#include "../utils/logger.h"

namespace VibrationSensor {

static bool available_ = false;

bool begin() {
  // Placeholder probe — replace with the actual accelerometer driver
  // init call, e.g. Drivers::Accelerometer::begin().
  available_ = true;
  Logger::info("VibrationSensor", available_ ? "Initialized" : "Not detected");
  return available_;
}

int readWindow(float* outBuffer, int count) {
  if (!available_) return 0;
  // Placeholder acquisition — replace with real accelerometer reads.
  for (int i = 0; i < count; i++) {
    outBuffer[i] = 0.0f;  // TODO: Drivers::Accelerometer::readG()
  }
  return count;
}

bool isAvailable() { return available_; }

}  // namespace VibrationSensor
