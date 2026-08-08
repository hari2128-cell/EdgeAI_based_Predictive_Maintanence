# System Block Diagram

```
 ┌─────────────┐     ┌───────────────┐     ┌─────────────────────┐
 │   Sensors   │────▶│     ESP32     │────▶│  Signal Processing  │
 │ (Vib+Audio) │     │ (Acquisition) │     │  (Filter/FFT/Feat.)  │
 └─────────────┘     └───────────────┘     └──────────┬───────────┘
                                                        ▼
 ┌─────────────┐     ┌───────────────┐     ┌─────────────────────┐
 │  Dashboard  │◀────│ Communication │◀────│      TinyML          │
 │ (React UI)  │     │ (MQTT / WiFi) │     │ (TFLite Micro Infer) │
 └─────────────┘     └───────────────┘     └──────────┬───────────┘
                                                        ▼
                                             ┌─────────────────────┐
                                             │  User Interface     │
                                             │ (OLED / LED / Buzzer)│
                                             └─────────────────────┘
```

**Blocks:**
- **Sensors** — vibration/accelerometer sensor + INMP441 microphone
- **ESP32** — acquisition + orchestration
- **Signal Processing** — DC removal, filtering, normalization, windowing, FFT, feature extraction
- **TinyML** — TensorFlow Lite Micro inference engine producing Healthy/Warning/Fault
- **Communication** — MQTT publish over Wi-Fi
- **Dashboard** — React frontend consuming MQTT/backend data
- **User Interface** — OLED status, LED indication, buzzer alarm
