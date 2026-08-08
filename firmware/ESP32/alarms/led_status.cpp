#include "led_status.h"

#include <Arduino.h>

#include "../app_config.h"

namespace LedStatus {

void begin() {
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_YELLOW, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);
}

void update(MachineState state) {
  digitalWrite(PIN_LED_GREEN, state == MachineState::HEALTHY ? HIGH : LOW);
  digitalWrite(PIN_LED_YELLOW, state == MachineState::WARNING ? HIGH : LOW);
  digitalWrite(PIN_LED_RED, state == MachineState::FAULT ? HIGH : LOW);
}

}  // namespace LedStatus
