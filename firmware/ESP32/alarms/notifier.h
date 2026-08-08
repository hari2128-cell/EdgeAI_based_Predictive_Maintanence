#ifndef NOTIFIER_H
#define NOTIFIER_H

#include "../app/app_state_machine.h"

// Coordinates all alarm outputs (LED + buzzer) and, on a state change
// into FAULT, triggers an immediate MQTT alert publish.
namespace Notifier {

void begin();
void onStateChanged(MachineState newState);

}  // namespace Notifier

#endif // NOTIFIER_H
