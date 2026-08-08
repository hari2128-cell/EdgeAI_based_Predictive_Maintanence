# TCP/IP

MQTT (and the dashboard backend's REST/WebSocket APIs) run over standard TCP/IP on top of the ESP32's WiFi (station mode) connection.

## Notes
- ESP32 obtains an IP address via DHCP from the local WiFi access point.
- MQTT broker is reached by hostname/IP on port 1883 (or 8883 for TLS).
- No static IP configuration is required for the default setup; a static IP / mDNS hostname could be added for more predictable broker discovery in a fixed installation.
- Firewall/router configuration must allow the ESP32 and the machine running the MQTT broker + dashboard backend to reach each other on the relevant ports (1883/8883, and the dashboard backend's port, default 4000).
