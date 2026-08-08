# Software Block Diagram

```
┌───────────────────────────────────────────────────────────┐
│                        app/ (Application Layer)             │
│   app_controller  ·  app_state_machine  ·  main.cpp          │
└───────────────────────────┬─────────────────────────────────┘
                             │
┌───────────────────────────▼─────────────────────────────────┐
│                    core/ (System Services)                    │
│   system_init  ·  diagnostics                                  │
└───────────────────────────┬─────────────────────────────────┘
                             │
┌───────────────┬───────────▼───────────┬───────────────────────┐
│  drivers/      │   sensors/            │  signal_processing/    │
│  (HW access)   │  (vibration, acoustic)│ (filters, FFT, features)│
└───────────────┴───────────┬───────────┴───────────────────────┘
                             │
┌───────────────────────────▼─────────────────────────────────┐
│                     tinyml/ (Inference Layer)                  │
│   inference.cpp  ·  model_data.h  ·  labels.h                   │
└───────────────────────────┬─────────────────────────────────┘
                             │
┌───────────────┬───────────▼───────────┬───────────────────────┐
│ display/       │  alarms/              │  communication/         │
│ (OLED UI)      │ (LED + buzzer)        │ (WiFi + MQTT)            │
└───────────────┴───────────────────────┴───────────────────────┘
```

**Firmware modules:** `app/`, `core/`, `drivers/`, `sensors/`, `signal_processing/`, `tinyml/`, `display/`, `alarms/`, `communication/`, `utils/`. See `firmware/README.md` for full responsibilities of each module.
