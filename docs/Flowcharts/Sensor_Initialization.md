# Sensor Initialization Flowchart

```
Start → Initialize I2C bus → Probe Accelerometer (fail → log error, sensor_ok=false) →
Initialize I2S bus → Probe INMP441 (fail → log error, sensor_ok=false) → Sensors Ready → End
```

If a sensor fails to initialize, the diagnostics module logs the failure and the system continues with the remaining functional sensors where possible, rather than halting.
