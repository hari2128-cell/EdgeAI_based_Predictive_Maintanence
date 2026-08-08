# Communication Architecture

## MQTT Topic Hierarchy
```
edgeai/<machine_id>/status
edgeai/<machine_id>/telemetry
edgeai/<machine_id>/alerts
edgeai/<machine_id>/diagnostics
```
If additional machines are added later, only `<machine_id>` changes (e.g. `edgeai/machine02/telemetry`), keeping the hierarchy scalable.

## Data Packet Structure

Telemetry (`edgeai/machine01/telemetry`):
```json
{
  "device_id": "machine01",
  "timestamp": "2026-07-17T10:30:00Z",
  "machine_state": "Healthy",
  "vibration_rms": 0.18,
  "dominant_frequency": 120,
  "audio_level": 0.42
}
```

Status (`edgeai/machine01/status`):
```json
{
  "device_id": "machine01",
  "wifi_connected": true,
  "mqtt_connected": true,
  "uptime_seconds": 5423,
  "firmware_version": "0.1.0"
}
```

Alerts (`edgeai/machine01/alerts`):
```json
{
  "device_id": "machine01",
  "timestamp": "2026-07-17T10:31:12Z",
  "severity": "Fault",
  "message": "High vibration detected"
}
```

## QoS Level
QoS 0 (at most once) is used for high-frequency telemetry to minimize overhead. QoS 1 (at least once) is recommended for `alerts`, since fault notifications should not be silently dropped.

## Connection Sequence
```
Power On → WiFi.begin() → Wait for WiFi connection →
mqttClient.connect() → Subscribe (if applicable) → Ready to Publish
```

## Reconnection Strategy
- WiFi: automatic retry with backoff; system continues local monitoring while disconnected.
- MQTT: reconnect attempt on every main loop iteration if disconnected; telemetry is skipped (not queued) until reconnected in the current implementation.

## Error Handling
| Condition | Action |
|---|---|
| WiFi lost | Retry connection; continue local inference & display |
| MQTT broker unreachable | Retry connect; skip publish this cycle |
| Malformed payload | Log and discard (should not occur under normal operation) |

## Security Considerations (Planned)
- TLS-secured MQTT (port 8883)
- Broker username/password authentication
- Per-device credentials for multi-machine deployments
