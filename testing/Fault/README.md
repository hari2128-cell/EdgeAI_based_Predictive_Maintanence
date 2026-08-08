# Fault State Testing

## Objective
Verify the system correctly classifies and reports a **Fault** machine condition end-to-end (sensors → signal processing → TinyML → state machine → OLED/LED/buzzer → MQTT).

## Test Procedure
1. Place the sensor rig on a machine (or simulated source) exhibiting fault characteristics (high vibration, abnormal acoustic signature).
2. Allow the system to run through several inference cycles (debounce requires 3 consistent predictions — see `firmware/ESP32/app/app_state_machine.cpp`).
3. Record the observed LED color, OLED text, buzzer state, and the MQTT telemetry/alert payloads.
4. Compare against the expected behavior below.

## Expected Behavior
- LED: Red
- OLED: "FAULT"
- Buzzer: Active
- MQTT `machine_state`: `"Fault"`, plus an immediate `edgeai/<machine_id>/alerts` publish (QoS 1)

## Log

| Date | Tester | Source | Observed LED | Observed OLED | Buzzer | MQTT Payload | Pass/Fail |
|---|---|---|---|---|---|---|---|
| _(no tests logged yet)_ | | | | | | | |
