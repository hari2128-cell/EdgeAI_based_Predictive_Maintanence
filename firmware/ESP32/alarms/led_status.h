#ifndef LED_STATUS_H
#define LED_STATUS_H

#include "../app/app_state_machine.h"

namespace LedStatus {

void begin();
void update(MachineState state);

}  // namespace LedStatus

#endif // LED_STATUS_H
