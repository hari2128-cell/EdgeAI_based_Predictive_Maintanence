#include "system_init.h"

#include <Arduino.h>
#include <Wire.h>

#include "../app_config.h"
#include "../utils/logger.h"
#include "diagnostics.h"

namespace SystemInit {

bool begin() {
  Logger::info("SystemInit", "Booting EdgeAI Predictive Maintenance firmware...");

  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_YELLOW, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(PIN_LED_GREEN, LOW);
  digitalWrite(PIN_LED_YELLOW, LOW);
  digitalWrite(PIN_LED_RED, LOW);
  digitalWrite(PIN_BUZZER, LOW);

  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);

  Diagnostics::logBoot("GPIO initialized");
  Diagnostics::logBoot("I2C bus initialized");

  return true;
}

}  // namespace SystemInit
