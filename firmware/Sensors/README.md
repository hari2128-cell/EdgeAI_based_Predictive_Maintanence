# Sensors (Reference Module)

Documents the hardware-independent sensor abstraction layer described in `docs/System_Architecture.md` §2.7 and §4.8. The buildable implementation lives at `firmware/ESP32/sensors/` (`vibration.cpp`, `acoustic.cpp`); this folder captures the same interfaces as standalone reference documentation.

**Responsibilities:** sampling, calibration (planned), basic validation, unit conversion, timestamping.

**Outputs:**
- Vibration: acceleration (g)
- Acoustic: amplitude, sample buffer

See `firmware/ESP32/sensors/vibration.h` and `acoustic.h` for the current interface definitions.
