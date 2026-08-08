# EdgeAI Predictive Maintenance

### Edge AI-based Predictive Maintenance for Industrial Machinery using ESP32, TinyML, and Real-Time Condition Monitoring

![Status](https://img.shields.io/badge/status-active--development-yellow)
![Platform](https://img.shields.io/badge/platform-ESP32-blue)
![AI](https://img.shields.io/badge/AI-TinyML%20%2F%20TensorFlow%20Lite-orange)
![License](https://img.shields.io/badge/license-MIT-green)
![Communication](https://img.shields.io/badge/protocol-MQTT-purple)

---

## 1. Overview

Industrial equipment such as induction motors, pumps, compressors, CNC machines, conveyors, and rotating machinery degrades gradually during operation. Bearing wear, shaft misalignment, rotor imbalance, loose assemblies, lubrication loss, and abnormal vibration often go undetected until they cause unexpected failure.

This project implements an **Edge AI predictive maintenance system** that performs real-time fault detection **directly on an ESP32 microcontroller**, without relying on cloud inference. Vibration and acoustic sensor data is processed locally, classified using a TinyML model (TensorFlow Lite Micro), and reported through OLED, LEDs, buzzer, and an MQTT-based dashboard.

## 2. Problem Statement

Most small and medium industries lack affordable predictive maintenance solutions. Existing commercial systems typically require expensive hardware, cloud infrastructure, or proprietary controllers. This project explores a cost-effective, edge-first alternative built entirely on commodity embedded hardware.

## 3. Key Features

- Real-time vibration + acoustic sensing (accelerometer + INMP441 MEMS microphone)
- On-device signal processing: filtering, windowing, FFT, feature extraction
- On-device TinyML inference (TensorFlow Lite Micro) — no cloud dependency
- 3-state machine health classification: **Healthy / Warning / Fault**
- Local feedback via OLED display, RGB LEDs, and buzzer
- MQTT-based telemetry publishing to a live web dashboard
- Modular, layered firmware architecture (drivers → sensors → signal processing → TinyML → communication)
- Designed for scalability: multi-sensor fusion, multi-machine fleets, OTA updates (planned)

## 4. System Architecture

```
Industrial Machine
      │
      ▼
Sensors (Vibration + Acoustic)
      │
      ▼
ESP32 Data Acquisition
      │
      ▼
Signal Preprocessing (Filter → Normalize → Window → FFT)
      │
      ▼
Feature Extraction
      │
      ▼
TinyML Inference (TensorFlow Lite Micro)
      │
      ▼
Health Classification (Healthy / Warning / Fault)
      │
      ├──► OLED Display
      ├──► LEDs
      ├──► Buzzer
      │
      ▼
MQTT Publisher ──► WiFi ──► MQTT Broker ──► Dashboard ──► Real-Time Monitoring
```

See [`docs/System_Architecture.pdf`](docs/System_Architecture.pdf) and [`docs/Project_Overview.md`](docs/Project_Overview.md) for details.

## 5. Hardware

| Component | Role |
|---|---|
| ESP32 Dev Module | Primary controller — sensing, DSP, TinyML inference, connectivity |
| Vibration Sensor / Accelerometer | Detects bearing wear, imbalance, misalignment |
| INMP441 MEMS Microphone (I²S) | Captures acoustic emissions / bearing & gear noise |
| 0.96" OLED Display (I²C) | Local status display |
| RGB Status LEDs | Green / Yellow / Red machine health indication |
| Buzzer | Audible fault alarm |
| Wi-Fi (onboard ESP32) | Telemetry to dashboard |

Full details: [`hardware/Components/`](hardware/Components/)

## 6. Software Stack

| Layer | Technology |
|---|---|
| Firmware | C++ (Arduino framework for ESP32), FreeRTOS (planned) |
| Machine Learning | Python, TensorFlow, TensorFlow Lite Micro |
| Signal Processing (offline validation) | NumPy, SciPy, MATLAB |
| Communication | MQTT, Wi-Fi, Serial UART |
| Dashboard | React, Vite, Tailwind CSS, MQTT.js, Recharts, Node.js backend |
| Tooling | VS Code, Arduino IDE / PlatformIO, Git |

## 7. Repository Structure

```
EdgeAI-Predictive-Maintenance/
│
├── README.md
├── LICENSE
├── .gitignore
│
├── docs/                 # Architecture, design decisions, flowcharts, reports
├── hardware/              # Components, circuit diagrams, PCB (added later), images
├── firmware/               # ESP32 embedded C++ firmware (modular)
├── tinyml/                 # Dataset, feature extraction, training, TFLite conversion
├── dashboard/              # React frontend + Node backend + MQTT broker config
├── communication/          # MQTT / TCP-IP / WiFi protocol documentation & configs
├── datasets/                # Raw, processed, and training-ready data
├── testing/                  # Test procedures & logs per machine state
├── images/                    # Project photos
├── videos/                     # Demo videos
└── results/                     # Model performance, dashboard, accuracy results
```

## 8. Machine Health States

| State | Trigger | LED | Buzzer | Dashboard |
|---|---|---|---|---|
| **Healthy** | Normal vibration & acoustic profile | Green | Off | Normal |
| **Warning** | Slight vibration/frequency deviation | Yellow | Off (short beep planned) | Warning |
| **Fault** | High vibration, abnormal acoustic signature | Red | Active | Fault alert + MQTT alert |

## 9. Setup Instructions

1. **Firmware:** Open `firmware/ESP32` in Arduino IDE / PlatformIO, install dependencies (see `firmware/README.md`), flash to ESP32.
2. **TinyML:** Follow `tinyml/README.md` to (re)train the model and regenerate `model_data.h`.
3. **Dashboard:** `cd dashboard/frontend && npm install && npm run dev`; `cd dashboard/backend && npm install && npm start`.
4. **MQTT Broker:** Use Mosquitto locally or a cloud broker — see `communication/MQTT/README.md`.

## 10. Project Workflow

```
Hardware Assembly → Firmware Bring-up → Sensor Validation →
Dataset Collection → Feature Engineering → Model Training →
TFLite Conversion → On-device Deployment → MQTT Integration →
Dashboard Development → System Testing → Documentation
```

## 11. Current Implementation Status

- [x] Repository architecture & documentation
- [x] Firmware module skeleton (drivers, sensors, signal processing, TinyML, comms)
- [x] Baseline TinyML training pipeline
- [x] Dashboard (frontend + backend) scaffold
- [ ] PCB design (to be added)
- [ ] FreeRTOS task scheduling (planned)
- [ ] OTA updates (planned)

## 12. Future Roadmap

See [`docs/Future_Roadmap.md`](docs/Future_Roadmap.md) — short/mid/long-term plans including multi-sensor fusion, Remaining Useful Life (RUL) estimation, fleet monitoring, and cloud sync.

## 13. Results

See [`results/`](results/) for model performance, accuracy metrics, and dashboard screenshots.

## 14. License

This project is licensed under the [MIT License](LICENSE).

## 15. Author

**EdgeAI Predictive Maintenance Project**
Embedded Systems · TinyML · Industrial IoT

## 16. Acknowledgements

Built using open-source tools: TensorFlow Lite Micro, Arduino/ESP32 core, Mosquitto MQTT, React, and the broader embedded ML community.
