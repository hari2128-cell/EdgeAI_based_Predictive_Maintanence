#include "buzzer_alarm.h"

#include <Arduino.h>

#include "../app_config.h"

namespace BuzzerAlarm {

void begin() {
  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(PIN_BUZZER, LOW);
}

void update(MachineState state) {
  // Fault -> continuous alert. Warning/Healthy -> silent.
  // A short intermittent beep pattern for Warning is a planned enhancement.
  digitalWrite(PIN_BUZZER, state == MachineState::FAULT ? HIGH : LOW);
}

}  // namespace BuzzerAlarm
