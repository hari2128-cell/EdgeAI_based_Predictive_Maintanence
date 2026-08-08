# Hardware Block Diagram

```
                 ┌────────────────────────┐
                 │        ESP32            │
                 │  (3.3V Dev Module)      │
                 │                          │
   I2C  ─────────┤ SDA/SCL     GPIO ──┐     │
   (OLED)         │                    │     │
                 │                    ▼     │
   I2S  ─────────┤ SD/SCK/WS   LED(R/Y/G) │
   (INMP441)      │                    ▲     │
                 │                    │     │
   Analog/I2C ───┤ ADC/GPIO   Buzzer─┘     │
   (Vibration)    │                          │
                 │        WiFi (2.4GHz)     │
                 └───────────┬──────────────┘
                             ▼
                        Wireless AP
```

## Power Supply
- ESP32 powered via USB (5V → onboard 3.3V regulator) or external 3.3–5V supply.
- Sensors (accelerometer, INMP441, OLED) run on 3.3V, powered directly from the ESP32 3V3 rail.
- Buzzer and LEDs are driven through GPIO with current-limiting resistors (LEDs) / transistor driver (buzzer, if needed).

## Sensor Interfaces
- **OLED (SSD1306):** I²C — SDA, SCL
- **INMP441 Microphone:** I²S — SD (data), SCK (bit clock), WS (word select)
- **Vibration Sensor / Accelerometer:** I²C or analog GPIO depending on module (see `hardware/Components/Accelerometer.md`)

## Communication Buses
- I²C bus shared by OLED and (if applicable) I²C-based accelerometer
- I²S bus dedicated to the microphone
- GPIO for LEDs, buzzer, and optional analog vibration sensor input

## External Peripherals
OLED display, RGB status LEDs, active buzzer, vibration sensor/accelerometer, INMP441 MEMS microphone.
