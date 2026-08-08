# Communication Reliability Testing

## Objective
Verify the firmware's WiFi/MQTT reconnection logic behaves correctly under interruption.

## Test Cases
1. **WiFi drop mid-operation** — disable the access point, confirm the firmware retries every `WIFI_RETRY_INTERVAL_MS` and local inference/display continue uninterrupted.
2. **MQTT broker restart** — stop/restart the Mosquitto broker, confirm `MqttManager::loop()` reconnects automatically once the broker is back.
3. **Malformed payload resilience** — verify the dashboard backend discards malformed JSON without crashing (see `dashboard/backend/services/mqttService.js`).
4. **Fault alert delivery** — confirm a Fault-state transition reliably triggers an immediate `edgeai/<machine_id>/alerts` publish, not just the next periodic telemetry cycle.

**Status:** Test cases defined; results pending hardware/network testing.
