#ifndef BUZZER_ALARM_H
#define BUZZER_ALARM_H

#include "../app/app_state_machine.h"

namespace BuzzerAlarm {

void begin();
void update(MachineState state);

}  // namespace BuzzerAlarm

#endif // BUZZER_ALARM_H
