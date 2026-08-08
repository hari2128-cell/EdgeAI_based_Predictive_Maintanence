#include "diagnostics.h"

#include "../utils/logger.h"

namespace Diagnostics {

void logBoot(const String& message) {
  Logger::info("BOOT", message);
}

void logError(const String& module, const String& message) {
  Logger::error(module.c_str(), message);
}

void logSensorStatus(const String& sensorName, bool ok) {
  if (ok) {
    Logger::info("SENSOR", sensorName + " OK");
  } else {
    Logger::warn("SENSOR", sensorName + " UNAVAILABLE - retrying next cycle");
  }
}

void logNetworkStatus(bool wifiConnected, bool mqttConnected) {
  Logger::info("NETWORK",
               String("WiFi=") + (wifiConnected ? "connected" : "disconnected") +
               " MQTT=" + (mqttConnected ? "connected" : "disconnected"));
}

}  // namespace Diagnostics
