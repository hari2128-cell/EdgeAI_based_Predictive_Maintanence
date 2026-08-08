#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

#include <Arduino.h>

namespace MqttManager {

void begin();
bool isConnected();
void loop();
bool publishTelemetry(const String& payload);
bool publishAlert(const String& payload);
bool publishStatus(const String& payload);

}  // namespace MqttManager

#endif // MQTT_MANAGER_H
