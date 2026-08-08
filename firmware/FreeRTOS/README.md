# FreeRTOS (Planned)

The current firmware (`firmware/ESP32`) uses a simple cooperative `loop()` scheduler. This folder is reserved for the planned migration to explicit FreeRTOS tasks, which the ESP32 Arduino core already runs under the hood (Arduino's `loop()` itself executes as a FreeRTOS task on core 1).

## Planned Task Breakdown
| Task | Core | Priority | Responsibility |
|---|---|---|---|
| `SensorTask` | 0 | High | Continuous vibration/audio sampling into circular buffers |
| `ProcessingTask` | 1 | Medium | Signal processing + feature extraction + TinyML inference |
| `CommsTask` | 1 | Low | WiFi/MQTT connection maintenance + telemetry publishing |
| `UITask` | 1 | Low | OLED/LED/buzzer updates |

## Why FreeRTOS?
- Deterministic timing for sensor sampling (currently coupled to the main loop interval)
- Sensor acquisition can continue uninterrupted while MQTT publishing or OLED rendering is in progress
- Enables future watchdog-per-task supervision

## Planned Files
`sensor_task.cpp/.h`, `processing_task.cpp/.h`, `comms_task.cpp/.h`, `ui_task.cpp/.h`, `task_config.h`

**Status:** Not yet implemented — the current `firmware/ESP32` project uses the cooperative loop described in `firmware/README.md`.
