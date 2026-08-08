# Boot Sequence Flowchart

```
Power On → Initialize Hardware (GPIO, I2C, I2S) → Initialize Sensors →
Initialize OLED → Connect WiFi (fail → retry/local mode only) →
Connect MQTT → Enter Main Loop
```

The boot sequence initializes hardware first, then sensors, then networking. If WiFi/MQTT fail, the system still proceeds to the main loop and continues local (offline) monitoring, retrying connectivity each cycle.
