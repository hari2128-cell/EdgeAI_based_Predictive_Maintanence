# Buzzer (Reference Module)

Documents alarm-layer responsibility: visual + audible alerts, alert escalation (planned).

| Machine State | LED | Buzzer |
|---|---|---|
| Healthy | Green | Off |
| Warning | Yellow | Short intermittent beep (planned) |
| Fault | Red | Continuous / repeated alert pattern |

Implementation: `firmware/ESP32/alarms/buzzer_alarm.cpp`, `led_status.cpp`, `notifier.cpp`.
