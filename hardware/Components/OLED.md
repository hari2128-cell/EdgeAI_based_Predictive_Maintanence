# OLED Display (0.96" I²C, SSD1306)

## Working Principle
A 128x64 monochrome OLED panel driven by the SSD1306 controller over I²C, used to render text/graphics for local status feedback.

## Specifications
| Parameter | Value |
|---|---|
| Resolution | 128x64 px |
| Interface | I²C |
| Supply Voltage | 3.3V |
| Controller | SSD1306 |

## Pin Configuration
| OLED Pin | ESP32 GPIO |
|---|---|
| SDA | GPIO 21 |
| SCL | GPIO 22 |
| VCC | 3.3V |
| GND | GND |

## Why It Was Selected
Low cost, low power, no backlight needed (self-emissive), widely supported Adafruit/U8g2 libraries for the ESP32.

## Alternatives
Character LCD (16x2) — considered but rejected due to limited graphical flexibility for status/prediction display.

## Limitations
Small screen size limits displayed information density; monochrome only.
