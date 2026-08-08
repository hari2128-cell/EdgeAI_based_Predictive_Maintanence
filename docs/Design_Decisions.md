# Design Decisions

For every major design choice: the problem, alternatives considered, the chosen solution, reasoning, and trade-offs.

## Why ESP32?
**Problem:** Need a low-cost controller capable of sensing, DSP, TinyML inference, and wireless connectivity.
**Alternatives:** Arduino Uno (too limited), Raspberry Pi (too costly/power-hungry for embedded deployment), STM32 (no built-in Wi-Fi).
**Chosen:** ESP32 — dual-core, built-in Wi-Fi, sufficient RAM/Flash for moderate TinyML workloads, large community support, compatible with TensorFlow Lite Micro, cost-effective.
**Trade-offs:** More limited memory/compute than application processors; not suitable for very large deep learning models; requires careful memory management.

## Why Edge AI (over Cloud AI)?
**Traditional:** Sensor → Cloud → Prediction (adds latency, bandwidth cost, and network dependency).
**Chosen:** Sensor → ESP32 → Prediction (Edge AI).
**Reasons:** Lower latency, reduced bandwidth, offline capability, improved privacy, local decision-making, reduced cloud dependency.
**Trade-offs:** Requires smaller, optimized models and more careful resource management than cloud-based inference.

## Why TinyML?
**Reasons:** Compact model deployment, real-time inference, low memory footprint, low power consumption, embedded deployment.
**Trade-offs:** Limited model complexity; quantization may reduce accuracy; resource constraints require optimization.

## Why Vibration Monitoring?
Mechanical faults often change vibration characteristics before visible failure occurs. Widely used in condition monitoring; sensitive to imbalance and misalignment.
**Limitations:** Sensor placement influences results; different machines exhibit different vibration signatures.

## Why Acoustic Monitoring?
Complements vibration analysis by capturing audible/ultrasonic characteristics not always visible in vibration alone. Non-contact information source.
**Trade-offs:** Sensitive to ambient noise; requires preprocessing for reliable features.

## Why Sensor Fusion?
Combining vibration + audio improves robustness and fault discrimination. Future possibilities: temperature, current, voltage, RPM.
**Trade-offs:** Increased processing, higher memory usage, more complex synchronization.

## Why FFT?
Mechanical faults often manifest as characteristic frequencies; frequency-domain analysis simplifies interpretation of periodic behavior.
**Trade-offs:** Computationally efficient and well understood, but assumes signal stationarity within the analysis window; resolution depends on window size and sampling rate.

## Why Feature Engineering (instead of raw signals)?
Reduces data dimensionality → lower computational cost, smaller model input, easier deployment on constrained hardware.
**Trade-offs:** Requires engineering judgment; poor feature choices can reduce model performance.

## Why MQTT?
Lightweight publish-subscribe protocol, efficient for embedded devices, supports multiple subscribers, easy dashboard integration.
**Trade-offs:** Requires a broker; security configuration must be considered.

## Why React Dashboard?
Component-based architecture for interactive UIs, efficient UI updates, rich ecosystem.
**Trade-offs:** Initial learning curve; requires a build system.

## Why MATLAB for Validation?
Mature DSP toolchain and powerful visualization used to validate filtering, inspect FFT outputs, and compare algorithms before embedded implementation.

## Why Modular Firmware?
Divided into functional modules for easier debugging, better code reuse, independent testing, improved readability.
**Trade-offs:** Slight increase in code organization effort; more interfaces to maintain.

## Decision Summary
| Design Area | Selected Approach | Primary Reason |
|---|---|---|
| Controller | ESP32 | Integrated Wi-Fi, suitable resources, cost-effective |
| AI | TinyML | On-device inference |
| Signal Analysis | FFT + feature extraction | Efficient fault characterization |
| Communication | MQTT | Lightweight telemetry |
| Dashboard | React + Tailwind | Modular, modern UI |
| Validation | MATLAB | DSP verification |
| Architecture | Modular | Maintainability and scalability |
