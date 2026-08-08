// =====================================================================
// EdgeAI Predictive Maintenance — ESP32 Firmware Entry Point
//
// This file is intentionally minimal. All business logic lives in
// app/app_controller.cpp. See firmware/README.md for the full module
// breakdown and build instructions.
// =====================================================================

#include "app/app_controller.h"
#include "core/system_init.h"

void setup() {
  Serial.begin(115200);
  delay(200);

  if (!SystemInit::begin()) {
    Serial.println("[FATAL] SystemInit failed");
  }

  AppController::begin();
}

void loop() {
  AppController::loop();
}
