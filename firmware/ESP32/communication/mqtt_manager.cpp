#include "mqtt_manager.h"

#include <PubSubClient.h>
#include <WiFi.h>

#include "../app_config.h"
#include "../utils/logger.h"
#include "wifi_manager.h"

namespace MqttManager {

namespace {
WiFiClient espClient;
PubSubClient mqttClient(espClient);
}  // namespace

void begin() {
  mqttClient.setServer(MQTT_BROKER, MQTT_PORT);
}

bool isConnected() { return mqttClient.connected(); }

void loop() {
  if (!WiFiManager::isConnected()) return;

  if (!mqttClient.connected()) {
    if (mqttClient.connect(MQTT_CLIENT_ID)) {
      Logger::info("MqttManager", "Connected to MQTT broker");
    } else {
      Logger::warn("MqttManager", "MQTT connect failed, rc=" + String(mqttClient.state()));
      return;
    }
  }
  mqttClient.loop();
}

bool publishTelemetry(const String& payload) {
  if (!isConnected()) return false;
  return mqttClient.publish(MQTT_TOPIC_TELEMETRY, payload.c_str());
}

bool publishAlert(const String& payload) {
  if (!isConnected()) return false;
  // QoS 1 is not natively supported by PubSubClient's default publish();
  // consider a QoS-capable MQTT client library for guaranteed delivery.
  return mqttClient.publish(MQTT_TOPIC_ALERTS, payload.c_str());
}

bool publishStatus(const String& payload) {
  if (!isConnected()) return false;
  return mqttClient.publish(MQTT_TOPIC_STATUS, payload.c_str());
}

}  // namespace MqttManager
