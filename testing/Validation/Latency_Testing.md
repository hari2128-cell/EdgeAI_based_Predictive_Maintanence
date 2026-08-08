# End-to-End Latency Testing

## Objective
Measure the time from sensor sample acquisition to MQTT telemetry publish, to confirm the system meets the target responsiveness for a predictive maintenance use case (near-real-time, not hard-real-time).

## Method
1. Instrument the firmware to log a timestamp at (a) start of window acquisition and (b) immediately after `MqttManager::publishTelemetry()` returns.
2. Compute the delta over multiple cycles.
3. Break down the delta by stage (acquisition, signal processing, inference, publish) using intermediate timestamps if finer granularity is needed.

## Expected Budget (approximate, to be measured)
| Stage | Budget |
|---|---|
| Sensor window acquisition | Bounded by `WINDOW_SIZE` / `SAMPLE_RATE_HZ` (256/1000 ≈ 256ms) |
| Signal processing + feature extraction | Sub-10ms range expected on ESP32 @ 240MHz for this window size |
| TinyML inference | Depends on model size; sub-10ms expected for the baseline MLP |
| MQTT publish | Network-dependent (local broker: low single-digit ms) |

**Status:** No measurements recorded yet — populate this table once hardware testing begins.
