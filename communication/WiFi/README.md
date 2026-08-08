# WiFi

## Configuration
The ESP32 connects in station (STA) mode using credentials in `firmware/ESP32/app_config.h` (`WIFI_SSID`, `WIFI_PASSWORD`).

## Connection Sequence
```
WiFi.mode(WIFI_STA) -> WiFi.begin(ssid, password) -> poll WiFi.status() until WL_CONNECTED
```

## Reconnection Strategy
Implemented in `firmware/ESP32/communication/wifi_manager.cpp`: if the connection drops, the firmware retries every `WIFI_RETRY_INTERVAL_MS` (default 5s) without blocking the main loop, so local sensing/inference/display continue uninterrupted during an outage.

## Limitations
Single-band 2.4GHz only (standard ESP32 hardware limitation); no captive-portal / WiFiManager-style provisioning UI in the current implementation (credentials are compiled into firmware) — a planned enhancement for field deployment.
