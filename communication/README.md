# Communication

Protocol-level documentation and configuration for how the ESP32 talks to the outside world. Firmware implementation lives in `firmware/ESP32/communication/`; this folder is the protocol/config reference layer.

```
communication/
├── README.md
├── MQTT/     # Topic design, payload schema, broker config reference
├── TCP_IP/   # Underlying networking notes
└── WiFi/     # WiFi connection/reconnection strategy
```
