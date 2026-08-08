#include "packet_builder.h"

#include <ArduinoJson.h>

#include "../app_config.h"
#include "../utils/constants.h"

namespace PacketBuilder {

String buildTelemetryPayload(const char* machineState,
                              const FeatureExtraction::FeatureVector& features) {
  StaticJsonDocument<256> doc;
  doc["device_id"] = DEVICE_ID;
  doc["machine_state"] = machineState;
  doc["vibration_rms"] = features.values[0];
  doc["dominant_frequency"] = features.values[5];
  doc["audio_level"] = features.values[7];

  String output;
  serializeJson(doc, output);
  return output;
}

String buildAlertPayload(const char* severity, const char* message) {
  StaticJsonDocument<192> doc;
  doc["device_id"] = DEVICE_ID;
  doc["severity"] = severity;
  doc["message"] = message;

  String output;
  serializeJson(doc, output);
  return output;
}

String buildStatusPayload(bool wifiConnected, bool mqttConnected,
                           unsigned long uptimeSeconds) {
  StaticJsonDocument<192> doc;
  doc["device_id"] = DEVICE_ID;
  doc["wifi_connected"] = wifiConnected;
  doc["mqtt_connected"] = mqttConnected;
  doc["uptime_seconds"] = uptimeSeconds;
  doc["firmware_version"] = FIRMWARE_VERSION;

  String output;
  serializeJson(doc, output);
  return output;
}

}  // namespace PacketBuilder
