# INMP441 MEMS Microphone

## Working Principle
The INMP441 is a digital I²S MEMS microphone with an integrated ADC, providing 24-bit audio samples directly over the I²S bus without needing an external analog front end.

## Specifications
| Parameter | Value |
|---|---|
| Interface | I²S (digital) |
| Resolution | 24-bit |
| SNR | ~61 dBA |
| Sensitivity | -26 dBFS |
| Supply Voltage | 1.8V–3.3V |
| Frequency Response | 60 Hz – 15 kHz |

## Pin Configuration
| INMP441 Pin | ESP32 GPIO |
|---|---|
| SD (Data Out) | GPIO 32 |
| SCK (Bit Clock) | GPIO 33 |
| WS (Word Select / LRCLK) | GPIO 25 |
| L/R | GND (left channel) |
| VDD | 3.3V |
| GND | GND |

## Why It Was Selected
Digital output avoids analog noise pickup common with electret microphones on long wires; adequate frequency response to capture bearing/gear noise and mechanical impacts; well supported by the ESP32 I2S driver.

## Alternatives
- Analog electret microphone + external ADC — more noise-prone, requires extra components.
- Other I²S MEMS mics (e.g., ICS-43434) — similar performance, INMP441 chosen for cost and availability.

## Limitations
Sensitive to ambient acoustic noise; single-channel (mono) capture in the current configuration; requires careful gain/preprocessing for reliable feature extraction.
