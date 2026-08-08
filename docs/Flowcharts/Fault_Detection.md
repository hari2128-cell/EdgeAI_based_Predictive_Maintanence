# Fault Detection Flowchart

```
TinyML Prediction
  → Fault? (Yes → Red LED, Activate Buzzer, Publish Alert QoS 1)
  → Warning? (Yes → Yellow LED)
  → else → Green LED (Healthy)
```

State transitions pass through the finite-state machine (`app_state_machine`) rather than being applied directly, preventing rapid unstable switching between states from noisy single-cycle predictions.
