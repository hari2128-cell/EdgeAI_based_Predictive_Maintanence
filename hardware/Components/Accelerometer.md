# Vibration Sensor / Accelerometer

## Working Principle
Measures acceleration (vibration amplitude) along one or more axes, converting mechanical motion into an electrical signal proportional to acceleration. Used to detect bearing wear, rotor imbalance, loose mounting, and shaft misalignment through changes in vibration amplitude and frequency content.

## Specifications (typical for a MEMS accelerometer such as ADXL345 / MPU6050-class module)
| Parameter | Value (typical) |
|---|---|
| Axes | 3 (X, Y, Z) |
| Interface | I²C (or SPI) |
| Range | ±2g to ±16g (selectable) |
| Resolution | 10–16 bit |
| Supply Voltage | 3.3V |
| Output Data Rate | Up to several kHz |

> Note: document the exact accelerometer module used in your build here (part number, datasheet link) once finalized.

## Pin Configuration
| Sensor Pin | ESP32 GPIO |
|---|---|
| SDA | GPIO 21 (shared I²C bus with OLED) |
| SCL | GPIO 22 (shared I²C bus with OLED) |
| VCC | 3.3V |
| GND | GND |

## Why It Was Selected
I²C-based MEMS accelerometers are low-cost, widely available, easy to interface with the ESP32, and provide sufficient bandwidth to capture the vibration signatures relevant to bearing/imbalance/misalignment faults at typical industrial rotating speeds.

## Alternatives
- Piezoelectric vibration sensors — higher frequency range and industrial-grade accuracy, but higher cost and require signal conditioning circuitry.
- Analog vibration switches — only provide threshold detection, not suitable for TinyML feature extraction.

## Limitations
Sensor placement significantly affects measured amplitude; different machines exhibit different baseline vibration signatures, requiring per-machine calibration/thresholds in a production deployment.
