# FSM (Reference Module)

Standalone reference documentation for the machine-health finite-state machine implemented at `firmware/ESP32/app/app_state_machine.cpp`.

## States
```
BOOT -> INITIALIZING -> HEALTHY <-> WARNING <-> FAULT -> (RECOVERY) -> HEALTHY
```

Transitions are driven by TinyML predictions (not raw sensor values) and are debounced — a new state is only committed after `kDebounceThreshold` (default 3) consecutive consistent predictions, preventing unstable rapid switching between states.

```
           Healthy
               │
       Minor anomaly
               ▼
           Warning
               │
       Severe anomaly
               ▼
             Fault
               │
      Recovery detected
               ▼
           Healthy
```
