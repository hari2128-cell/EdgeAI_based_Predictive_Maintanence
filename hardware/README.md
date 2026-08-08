# Hardware

Contains all hardware-related documentation for the EdgeAI Predictive Maintenance system, except PCB design (added separately — see `PCB/`).

## Structure
```
hardware/
├── Components/       # One markdown file per hardware component
├── Circuit_Diagram/  # Wiring, signal flow, power distribution
├── PCB/              # Reserved — PCB design files added later
└── Images/           # Hardware setup / wiring / prototype photos
```

## Bill of Materials (BOM)
| Component | Qty | Purpose |
|---|---|---|
| ESP32 Dev Module | 1 | Primary controller |
| Vibration Sensor / Accelerometer | 1 | Mechanical fault detection |
| INMP441 MEMS Microphone | 1 | Acoustic emission sensing |
| 0.96" OLED Display (SSD1306, I²C) | 1 | Local status display |
| Green / Yellow / Red LED | 3 | Machine health indication |
| Active Buzzer | 1 | Audible fault alarm |
| Resistors (220Ω–330Ω) | 3+ | LED current limiting |
| Breadboard + Jumper Wires | — | Prototyping |
| Micro-USB / USB-C Cable | 1 | Programming & power |

See `Components/` for detailed specs on each part.
