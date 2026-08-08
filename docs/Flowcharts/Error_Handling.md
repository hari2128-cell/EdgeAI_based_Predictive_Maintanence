# Error Handling Flowchart

```
Error Detected → Classify Error Type:
  Sensor Unavailable → Retry init + report
  WiFi Lost          → Reconnect + continue local mode
  MQTT Unavailable    → Reconnect + skip publish
  Invalid Reading      → Discard sample
  Inference Failure     → Use last valid state + log error
```

Every error path logs a diagnostic message via `core/diagnostics` and, wherever possible, allows the system to continue operating rather than halting.
