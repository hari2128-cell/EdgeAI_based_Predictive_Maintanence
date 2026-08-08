# Testing

Test procedures, logs, and validation results demonstrating that the system correctly detects each machine state, plus overall validation methodology.

```
testing/
├── README.md
├── Healthy/     # Test logs/results while the machine was in a known-healthy condition
├── Warning/     # Test logs/results under induced/observed early-anomaly conditions
├── Fault/       # Test logs/results under induced/observed fault conditions
└── Validation/  # Cross-cutting validation: end-to-end latency, MQTT reliability, repeatability
```

## Test Methodology
1. **Per-state functional tests** — run the assembled system against a machine (or simulated vibration/audio source) in each of the three target conditions, and confirm the correct LED/OLED/buzzer/MQTT output.
2. **Signal processing validation** — compare on-device FFT/feature outputs against an offline Python/MATLAB reference (see `docs/Report/Project_Report.md` §3).
3. **Communication reliability** — verify MQTT reconnection behavior after broker/WiFi interruption (see `Validation/Communication_Reliability.md`).
4. **End-to-end latency** — measure time from sensor sample to MQTT publish (see `Validation/Latency_Testing.md`).

## Test Log Format
Each test log should record: date, tester, machine/source used, expected state, observed LED color, observed OLED text, observed buzzer behavior, MQTT payload received, pass/fail.

**Status:** Test procedure templates below are ready to use; populate with actual logged results as tests are run against the assembled hardware.
