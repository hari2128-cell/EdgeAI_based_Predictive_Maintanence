# EdgeAI Predictive Maintenance — Project Report

## Abstract
This report presents the design and implementation of an Edge AI-based predictive maintenance system for industrial rotating machinery. The system uses an ESP32 microcontroller to acquire vibration and acoustic sensor data, perform on-device digital signal processing and feature extraction, and run a TensorFlow Lite Micro model to classify machine health into Healthy, Warning, or Fault states — entirely without cloud dependency. Results are reported locally (OLED, LEDs, buzzer) and remotely via MQTT to a live dashboard.

## 1. Introduction
See `docs/Project_Overview.md` for the full problem statement, motivation, and objectives.

## 2. System Design
See `docs/System_Architecture.md` for the layered architecture, hardware architecture, firmware architecture, and data flow.

## 3. Methodology
1. Hardware assembly and sensor bring-up
2. Firmware development (modular driver → sensor → signal processing → TinyML → communication pipeline)
3. Dataset collection across three machine states
4. Feature engineering and model training (`tinyml/`)
5. TensorFlow Lite Micro conversion and on-device deployment
6. MQTT integration and dashboard development
7. System-level testing (`testing/`)

## 4. Results
Refer to `results/Model_Performance/`, `results/Accuracy/`, and `results/Dashboard/` for measured outcomes as they become available. This report avoids stating unmeasured numerical results as fact; all reported figures are sourced from the corresponding results files.

## 5. Discussion
The chosen edge-first architecture successfully removes dependency on cloud connectivity for the critical inference path, at the cost of requiring careful memory and compute budgeting on the ESP32 (see `docs/Design_Decisions.md`).

## 6. Limitations
- Dataset diversity may be limited during initial development
- Vibration signatures vary across different machine types
- Acoustic sensing is sensitive to ambient noise
- Broader validation across operating conditions is ongoing

## 7. Conclusion
The project demonstrates a working, cost-effective predictive maintenance platform suitable both as an educational reference and as a foundation for further industrial development.

## 8. Future Work
See `docs/Future_Roadmap.md`.

## Appendices
- Appendix A: Firmware module reference — `firmware/README.md`
- Appendix B: TinyML pipeline reference — `tinyml/README.md`
- Appendix C: Communication protocol reference — `communication/MQTT/README.md`
