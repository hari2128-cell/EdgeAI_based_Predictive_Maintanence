# Data Collection

Scripts for logging labeled sensor data from the ESP32 to build the training dataset in `tinyml/Dataset/`.

## Purpose
Stream raw/windowed vibration + audio samples from the ESP32 (running a "logging mode" firmware build) over serial, tagging each session with a ground-truth label (Healthy / Warning / Fault).

## Inputs
- ESP32 connected via USB, running firmware with serial CSV logging enabled
- Operator-assigned label for the current recording session

## Outputs
- CSV files under `tinyml/Dataset/<Label>/`

## Usage
```bash
python log_serial_to_csv.py --port /dev/ttyUSB0 --baud 115200 --label Healthy --duration 60 \
    --out ../Dataset/Healthy/healthy_session01_20260601.csv
```

## Dependencies
`pyserial`, `pandas`

## Status
Implemented as a reference script. Requires a firmware build with a serial CSV logging mode (print `timestamp,accel_x,accel_y,accel_z,audio_sample` once per sample) — not the default inference-mode firmware in `firmware/ESP32/`.
