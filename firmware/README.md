# Firmware

Modular ESP32 firmware for the EdgeAI Predictive Maintenance system, written in C++ using the Arduino framework for ESP32 (PlatformIO or Arduino IDE compatible).

## Philosophy
The firmware is designed as a modular embedded application rather than a single `.ino` file. Each module has one responsibility (Single Responsibility Principle), making the code easier to maintain, test, and extend.

## Folder Structure
```
firmware/
├── README.md
├── ESP32/                  # Main firmware source (this is the buildable project)
│   ├── ESP32.ino            # Arduino entry point (thin wrapper -> app/main)
│   ├── app_config.h          # Pin map, thresholds, WiFi/MQTT credentials placeholder
│   ├── app/                   # app_controller, app_state_machine
│   ├── core/                   # system_init, diagnostics
│   ├── utils/                   # logger, constants, timer, helpers
│   ├── signal_processing/        # filters, normalization, fft, feature_extraction
│   ├── sensors/                    # vibration, acoustic sensor abstraction
│   ├── tinyml/                      # inference wrapper, labels, model_data
│   ├── communication/                # wifi_manager, mqtt_manager, packet_builder
│   ├── display/                        # oled_ui
│   └── alarms/                          # led_status, buzzer_alarm, notifier
│
├── FreeRTOS/                # Planned: FreeRTOS task definitions (not yet active)
├── Drivers/                 # Hardware drivers, one folder per peripheral (reference docs + code)
├── Sensors/                 # Reference module docs
├── MQTT/                    # Reference module docs
├── OLED/                    # Reference module docs
├── Buzzer/                  # Reference module docs
└── FSM/                     # Reference module docs
```

> Note: `ESP32/` contains the actual buildable firmware project. The top-level `Drivers/`, `Sensors/`, `MQTT/`, `OLED/`, `Buzzer/`, and `FSM/` folders mirror the architecture in `docs/System_Architecture.md` §4 as standalone documented reference modules, useful for browsing the design layer-by-layer.

## Build Instructions

### Arduino IDE
1. Install the ESP32 board package (Boards Manager → `esp32` by Espressif).
2. Install libraries: `Adafruit SSD1306`, `Adafruit GFX`, `PubSubClient`, `ArduinoJson`, `TensorFlowLite_ESP32`.
3. Open `firmware/ESP32/ESP32.ino`.
4. Select your ESP32 board + COM port, then Upload.

### PlatformIO
```
cd firmware/ESP32
pio run --target upload
pio device monitor
```

## Firmware Execution Sequence
```
Power ON → Initialize Hardware → Initialize Sensors → Initialize WiFi →
Initialize MQTT → Collect Sensor Data → Filter Signals → Extract Features →
Run TinyML → Determine Machine Health → Update OLED → Update LEDs →
Trigger Alarm if Required → Publish MQTT → Repeat
```

## Module Responsibilities
| Module | Responsibility |
|---|---|
| `app_controller` | Coordinates the full sense → process → infer → act loop |
| `app_state_machine` | Governs Healthy/Warning/Fault transitions (debounced) |
| `system_init` | GPIO/peripheral/sensor/display/network bring-up |
| `diagnostics` | Boot logs, error reporting, sensor/network status |
| `Drivers/*` | Hardware-specific code only — no business logic |
| `Sensors/*` | Hardware-independent sampling, timestamping, unit conversion |
| `signal_processing/` | Filtering, normalization, windowing, FFT, feature extraction |
| `tinyml/inference` | TensorFlow Lite Micro wrapper |
| `communication/` | WiFi + MQTT connection, reconnection, publishing |
| `display/` | Status screen rendering |
| `alarms/` | Visual/audible alarm output |

## Error Handling Strategy
| Error | Action |
|---|---|
| Sensor unavailable | Retry initialization, report status via diagnostics |
| WiFi disconnected | Attempt reconnection while continuing local monitoring |
| MQTT unavailable | Skip telemetry this cycle; continue inference |
| Invalid sensor reading | Discard sample, continue |
| TinyML inference failure | Report diagnostic error, retain last known valid state |

## Future Firmware Enhancements
- FreeRTOS-based task scheduling (replacing the cooperative loop)
- Watchdog timer support
- OTA firmware updates
- Quantized model hot-swapping
