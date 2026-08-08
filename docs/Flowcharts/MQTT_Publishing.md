# MQTT Publishing Flowchart

```
Machine State + Telemetry → WiFi Connected? (No → skip publish) →
MQTT Connected? (No → attempt reconnect, fail → skip publish) →
Build JSON Payload → Publish to edgeai/<machine_id>/telemetry →
Fault State? (Yes → also publish edgeai/<machine_id>/alerts, QoS 1) → End
```
