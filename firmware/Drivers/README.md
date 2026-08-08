# Drivers

Hardware-specific driver modules — the only layer allowed to talk directly to peripherals/registers. Application and sensor-abstraction code call into these drivers, never the other way around.

Each subfolder documents and implements a single peripheral driver as a standalone reference module (mirroring `docs/System_Architecture.md` §4.7 / `firmware/README.md`). The buildable Arduino project (`firmware/ESP32`) currently inlines equivalent minimal logic directly in `sensors/`, `display/`, `communication/`, and `alarms/` for simplicity of a single-sketch build; as the project migrates to a PlatformIO multi-file library layout, these become the canonical driver implementations.

| Driver | Peripheral | Bus |
|---|---|---|
| `accelerometer/` | Vibration sensor | I²C |
| `microphone/` | INMP441 | I²S |
| `oled/` | SSD1306 display | I²C |
| `buzzer/` | Active buzzer | GPIO |
| `led/` | Status LEDs | GPIO |
| `wifi/` | ESP32 WiFi | — |
| `mqtt/` | MQTT client | TCP/IP over WiFi |
