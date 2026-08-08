# Circuit Diagram

Schematic files (KiCad/Fritzing/image exports) can be added here later. This document describes the wiring, signal flow, and power distribution in the meantime.

## Full Pin Mapping
| Peripheral | Signal | ESP32 GPIO |
|---|---|---|
| OLED (I²C) | SDA | 21 |
| OLED (I²C) | SCL | 22 |
| Accelerometer (I²C, shared bus) | SDA | 21 |
| Accelerometer (I²C, shared bus) | SCL | 22 |
| INMP441 (I²S) | SD | 32 |
| INMP441 (I²S) | SCK | 33 |
| INMP441 (I²S) | WS | 25 |
| Green LED | Signal | 27 |
| Yellow LED | Signal | 26 |
| Red LED | Signal | 14 |
| Buzzer | Signal | 12 |

## Wiring Details
1. Connect all 3.3V-tolerant peripherals (OLED, accelerometer, INMP441) to the ESP32's 3V3 pin — **do not** power them from 5V.
2. Share GND across all peripherals and the ESP32.
3. Add a 220–330Ω resistor in series with each LED's anode.
4. Connect the buzzer signal pin directly to its assigned GPIO (active buzzer — no driver transistor required at low current draw).

## Signal Flow
```
Vibration → Accelerometer → I2C → ESP32 peripheral bus → Signal Processing
Sound     → INMP441       → I2S → ESP32 I2S peripheral  → Signal Processing
ESP32 → I2C → OLED (status output)
ESP32 → GPIO → LEDs (health indication)
ESP32 → GPIO → Buzzer (fault alarm)
```

## Power Distribution
- ESP32 powered via USB (5V input, onboard regulator provides 3.3V).
- All sensors/peripherals draw from the ESP32's regulated 3.3V rail.
- Estimated total peripheral current draw is low (< 100 mA combined); a dedicated external 3.3V supply is recommended for field deployment to avoid brownouts during Wi-Fi transmit bursts.

*(Actual schematic diagrams — KiCad/Fritzing exports — will be added to this folder alongside the PCB design.)*
