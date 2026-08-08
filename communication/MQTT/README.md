# MQTT

## Why MQTT?
Lightweight publish-subscribe protocol well suited to embedded devices: low bandwidth, supports multiple subscribers, and integrates easily with a dashboard. See `docs/Design_Decisions.md` for the full comparison against alternatives.

## Topic Hierarchy
```
edgeai/<machine_id>/status
edgeai/<machine_id>/telemetry
edgeai/<machine_id>/alerts
edgeai/<machine_id>/diagnostics
```

## Payload Schemas

**Telemetry:**
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

**Status:**
```json
{
  "device_id": "machine01",
  "wifi_connected": true,
  "mqtt_connected": true,
  "uptime_seconds": 5423,
  "firmware_version": "0.1.0"
}
```

**Alerts:**
```json
{
  "device_id": "machine01",
  "severity": "Fault",
  "message": "High vibration detected"
}
```

## QoS
- Telemetry/Status: QoS 0 (frequent, loss-tolerant)
- Alerts: QoS 1 (should not be silently dropped)

## Broker
Reference local config: `dashboard/mqtt_broker/mosquitto.conf`. Firmware connection logic: `firmware/ESP32/communication/mqtt_manager.cpp`.

## Security (Planned)
TLS on port 8883, broker username/password, per-device credentials.
