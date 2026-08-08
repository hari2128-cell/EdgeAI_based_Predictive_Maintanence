# Warning State Testing

## Objective
Verify the system correctly classifies and reports a **Warning** machine condition end-to-end (sensors → signal processing → TinyML → state machine → OLED/LED/buzzer → MQTT).

## Test Procedure
1. Place the sensor rig on a machine (or simulated source) exhibiting early-anomaly characteristics (slight vibration increase, minor frequency deviation).
2. Allow the system to run through several inference cycles (debounce requires 3 consistent predictions — see `firmware/ESP32/app/app_state_machine.cpp`).
3. Record the observed LED color, OLED text, buzzer state, and the MQTT telemetry payload.
4. Compare against the expected behavior below.

## Expected Behavior
- LED: Yellow
- OLED: "Warning"
- Buzzer: Off (short intermittent beep planned)
- MQTT `machine_state`: `"Warning"`

## Log

| Date | Tester | Source | Observed LED | Observed OLED | Buzzer | MQTT Payload | Pass/Fail |
|---|---|---|---|---|---|---|---|
| _(no tests logged yet)_ | | | | | | | |
