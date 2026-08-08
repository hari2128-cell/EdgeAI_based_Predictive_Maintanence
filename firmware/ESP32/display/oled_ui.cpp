#include "oled_ui.h"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#include "../app_config.h"
#include "../utils/logger.h"

namespace OledUI {

namespace {
constexpr int SCREEN_WIDTH = 128;
constexpr int SCREEN_HEIGHT = 64;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
}  // namespace

bool begin() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Logger::error("OledUI", "SSD1306 allocation failed");
    return false;
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.display();
  return true;
}

void showBootScreen() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("EdgeAI Predictive");
  display.println("Maintenance");
  display.println();
  display.println("Booting...");
  display.display();
}

void showInitializingScreen() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Initializing...");
  display.display();
}

void showStatusScreen(const char* machineState, float vibrationRms,
                       float dominantFrequency, bool wifiConnected, bool mqttConnected) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println(machineState);

  display.setTextSize(1);
  display.setCursor(0, 20);
  display.printf("Vib RMS: %.2f g\n", vibrationRms);
  display.printf("Freq: %.0f Hz\n", dominantFrequency);
  display.printf("WiFi: %s\n", wifiConnected ? "OK" : "--");
  display.printf("MQTT: %s\n", mqttConnected ? "OK" : "--");
  display.display();
}

}  // namespace OledUI
