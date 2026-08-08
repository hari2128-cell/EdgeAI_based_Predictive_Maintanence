# TinyML Inference Flowchart

```
Feature Vector → Copy into Input Tensor → interpreter.Invoke()
  (fail → log error, keep last valid state)
→ Read Output Tensor (3 class scores) → argmax(scores) → predicted class →
Map to Machine State (Healthy / Warning / Fault) → Update State Machine
```

Inference failures do not crash the system; the last known valid machine state is retained and a diagnostic error is logged.
