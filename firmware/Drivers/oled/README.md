# OLED Driver (SSD1306)

**Responsibilities:** initialize display, render text, update status, display connection information.

The buildable firmware wraps this with a higher-level UI layer at `firmware/ESP32/display/oled_ui.cpp` using the Adafruit_SSD1306 library; this folder documents the driver-level responsibility in isolation per the layered architecture in `docs/System_Architecture.md`.
