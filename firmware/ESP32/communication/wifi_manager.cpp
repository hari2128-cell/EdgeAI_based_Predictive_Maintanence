#include "wifi_manager.h"

#include <WiFi.h>

#include "../app_config.h"
#include "../utils/logger.h"
#include "../utils/timer.h"

namespace WiFiManager {

namespace {
IntervalTimer retryTimer(WIFI_RETRY_INTERVAL_MS);
}

void begin() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Logger::info("WiFiManager", "Connecting to WiFi...");
}

bool isConnected() { return WiFi.status() == WL_CONNECTED; }

void loop() {
  if (isConnected()) return;
  if (retryTimer.ready()) {
    Logger::warn("WiFiManager", "WiFi disconnected, retrying...");
    WiFi.disconnect();
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  }
}

}  // namespace WiFiManager
