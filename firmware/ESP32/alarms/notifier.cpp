#include "notifier.h"

#include "../communication/mqtt_manager.h"
#include "../communication/packet_builder.h"
#include "../utils/logger.h"
#include "buzzer_alarm.h"
#include "led_status.h"

namespace Notifier {

void begin() {
  LedStatus::begin();
  BuzzerAlarm::begin();
}

void onStateChanged(MachineState newState) {
  LedStatus::update(newState);
  BuzzerAlarm::update(newState);

  if (newState == MachineState::FAULT) {
    Logger::warn("Notifier", "FAULT detected - publishing immediate alert");
    String payload = PacketBuilder::buildAlertPayload("Fault", "High vibration / abnormal signature detected");
    MqttManager::publishAlert(payload);
  }
}

}  // namespace Notifier
