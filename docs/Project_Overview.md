# Project Overview

## What This Project Is
EdgeAI Predictive Maintenance is an embedded system that continuously monitors the health of rotating industrial machinery (motors, pumps, compressors, conveyors, CNC machines, etc.) using vibration and acoustic sensing, and classifies machine condition — **Healthy**, **Warning**, or **Fault** — using an on-device (edge) machine learning model running on an ESP32 microcontroller.

## Why It Exists
Unexpected machine failure is one of the leading causes of industrial downtime. Reactive maintenance (fix after failure) is costly and disruptive; preventive maintenance (fixed schedules) wastes resources servicing healthy equipment. Predictive maintenance — acting on the *actual condition* of a machine — solves both problems, but commercial predictive maintenance systems are typically expensive, cloud-dependent, and inaccessible to small and medium industries.

This project demonstrates that a **low-cost, edge-first predictive maintenance platform** can be built using an ESP32, common MEMS sensors, and TinyML — without any dependency on cloud infrastructure for the critical inference path.

## Industrial Relevance
The same architecture generalizes to a wide range of rotating machinery: induction motors, pumps, compressors, gearboxes, cooling fans, conveyor systems, CNC machines, HVAC systems, wind turbines, robotic arms, industrial bearings, and agricultural machinery.

## Objectives
1. Design an embedded condition-monitoring system using ESP32.
2. Acquire vibration and acoustic signals from industrial machinery.
3. Preprocess sensor data to reduce environmental noise.
4. Extract meaningful diagnostic features (time-domain and frequency-domain).
5. Train lightweight ML models on the collected dataset.
6. Deploy TensorFlow Lite Micro models to the ESP32.
7. Perform real-time inference with no cloud dependency.
8. Display machine health locally (OLED / LEDs / buzzer) and remotely (dashboard).
9. Publish monitoring data over MQTT.
10. Provide a live dashboard for visualization and analytics.
11. Keep the software architecture modular for future expansion.

## Features Summary
- Edge AI inference (no cloud required for classification)
- Dual-modality sensing: vibration + acoustic
- On-device DSP pipeline: filtering → normalization → windowing → FFT → feature extraction
- 3-class machine health output with local + remote reporting
- MQTT telemetry to a React-based live dashboard
- Modular, layered firmware for maintainability and future sensor additions

## Current Implementation Status
| Module | Status |
|---|---|
| Firmware architecture & drivers | Implemented (skeleton + core logic) |
| Signal processing pipeline | Implemented |
| TinyML training pipeline | Implemented (baseline) |
| On-device inference | Implemented |
| MQTT communication | Implemented |
| Dashboard (frontend + backend) | Implemented (baseline) |
| PCB | Planned — to be added |
| FreeRTOS multitasking | Planned |
| OTA updates | Planned |
| Historical logging / analytics | Planned |

## Planned Enhancements
- FreeRTOS-based task scheduling for deterministic timing
- Watchdog timer support
- Quantized TFLite models for reduced memory footprint
- Confidence-score reporting and trend visualization
- Multi-sensor fusion (temperature, current, voltage, RPM)
- Remaining Useful Life (RUL) estimation
- Multi-device fleet management and cloud synchronization

See [`Future_Roadmap.md`](Future_Roadmap.md) for a categorized roadmap.
