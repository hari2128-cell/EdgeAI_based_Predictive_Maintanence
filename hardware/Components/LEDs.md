# Status LEDs (Green / Yellow / Red)

## Working Principle
Discrete GPIO-driven LEDs provide immediate, at-a-glance machine health indication without requiring the operator to read the OLED or dashboard.

## Specifications
| Parameter | Value |
|---|---|
| Type | Standard 5mm LED (Green, Yellow, Red) |
| Forward Voltage | ~2.0–2.2V (varies by color) |
| Current Limiting Resistor | 220Ω–330Ω |

## Pin Configuration
| LED | ESP32 GPIO |
|---|---|
| Green (Healthy) | GPIO 27 |
| Yellow (Warning) | GPIO 26 |
| Red (Fault) | GPIO 14 |

## Why It Was Selected
Simplest, lowest-cost, most reliable way to provide an unambiguous local health indicator visible from a distance on a factory floor.

## Alternatives
Single RGB LED — considered, but three discrete LEDs were chosen for unambiguous simultaneous visibility and simpler driving logic.

## Limitations
Only 3 discrete states can be shown; no intensity/confidence indication (unless PWM-driven brightness is added in future).
