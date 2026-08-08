# ESP32 Dev Module

## Working Principle
The ESP32 is a dual-core Xtensa LX6 microcontroller with integrated Wi-Fi and Bluetooth. It runs the application firmware, executes signal processing and TinyML inference, drives peripherals, and communicates over MQTT.

## Specifications
| Parameter | Value |
|---|---|
| CPU | Dual-core Xtensa LX6, up to 240 MHz |
| RAM | ~520 KB SRAM |
| Flash | 4 MB (typical dev module) |
| Wi-Fi | 802.11 b/g/n, 2.4 GHz |
| Bluetooth | Classic + BLE |
| Operating Voltage | 3.3V (5V via USB, regulated onboard) |
| GPIO | Up to 34 usable pins (dev-module dependent) |
| ADC | 12-bit SAR ADC |
| Peripherals | I2C, I2S, SPI, UART, PWM |

## Pin Configuration
| Function | GPIO |
|---|---|
| I2C SDA (OLED) | GPIO 21 |
| I2C SCL (OLED) | GPIO 22 |
| I2S SD (INMP441) | GPIO 32 |
| I2S SCK (INMP441) | GPIO 33 |
| I2S WS (INMP441) | GPIO 25 |
| Vibration Sensor (Analog/I2C) | GPIO 34 (ADC) or I2C shared bus |
| Green LED | GPIO 27 |
| Yellow LED | GPIO 26 |
| Red LED | GPIO 14 |
| Buzzer | GPIO 12 |

## Why It Was Selected
Built-in Wi-Fi removes the need for a separate networking module; dual-core architecture allows sensing/DSP work on one core while networking runs on the other; sufficient RAM/Flash for a quantized TinyML model; strong community and TensorFlow Lite Micro support; low cost.

## Alternatives Considered
- **Arduino Uno/Nano** — insufficient RAM/compute for FFT + TinyML, no built-in wireless.
- **Raspberry Pi** — capable, but higher cost, power draw, and boot complexity for an always-on embedded sensor node.
- **STM32** — good compute, but requires an external Wi-Fi module, increasing BOM complexity.

## Limitations
Limited RAM compared to application processors; not suited for large deep learning models; requires careful tensor-arena sizing for TFLite Micro.
