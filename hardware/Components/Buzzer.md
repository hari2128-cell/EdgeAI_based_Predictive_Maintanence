# Buzzer

## Working Principle
An active buzzer driven by a single GPIO pin, generating an audible tone to alert operators of a Fault condition without requiring them to be looking at the device.

## Specifications
| Parameter | Value |
|---|---|
| Type | Active buzzer (has internal oscillator) |
| Operating Voltage | 3.3V–5V |
| Drive | Direct GPIO |

## Pin Configuration
| Buzzer Pin | ESP32 GPIO |
|---|---|
| Signal | GPIO 12 |
| GND | GND |

## Why It Was Selected
Active buzzers simplify firmware (no tone-generation code needed) compared to passive buzzers, and provide a clear, unmistakable audible fault alert.

## Alternatives
Passive buzzer with PWM-driven tones — considered for future work to support distinct Warning vs Fault alert patterns.

## Limitations
Currently only a single fixed tone/pattern is supported (fault-only activation); differentiated Warning beep patterns are a planned enhancement.
