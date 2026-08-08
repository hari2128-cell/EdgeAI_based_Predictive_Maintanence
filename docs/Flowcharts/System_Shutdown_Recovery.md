# System Shutdown / Recovery Flowchart

```
Power Loss / Reset → On Next Power-On: Re-run Boot Sequence →
Restore Default State (BOOT → INITIALIZING) →
Re-acquire Sensors, WiFi, MQTT → Resume Monitoring Loop
```

The system holds no persistent state across power cycles in the current implementation; it always restarts from BOOT. Recovery from a transient fault (e.g., a temporary vibration spike) is handled by the state machine's Fault → Healthy transition once readings return to normal, without requiring a reset.
