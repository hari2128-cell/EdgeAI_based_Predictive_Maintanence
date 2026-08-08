#include "acoustic.h"

#include <Arduino.h>

#include "../app_config.h"
#include "../utils/logger.h"

namespace AcousticSensor {

static bool available_ = false;

bool begin() {
  // Placeholder — replace with i2s_driver_install()/i2s_set_pin() calls
  // configured for PIN_I2S_SD/SCK/WS from app_config.h.
  available_ = true;
  Logger::info("AcousticSensor", available_ ? "Initialized" : "Not detected");
  return available_;
}

int readWindow(float* outBuffer, int count) {
  if (!available_) return 0;
  for (int i = 0; i < count; i++) {
    outBuffer[i] = 0.0f;  // TODO: i2s_read + normalize
  }
  return count;
}

bool isAvailable() { return available_; }

}  // namespace AcousticSensor
