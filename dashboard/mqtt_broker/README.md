# MQTT Broker

Local development broker configuration (Eclipse Mosquitto).

## Install & Run (Mosquitto)
```bash
# Debian/Ubuntu
sudo apt install mosquitto mosquitto-clients

# Run with this repo's config
mosquitto -c mosquitto.conf
```

## Testing
```bash
# Subscribe to everything the dashboard cares about
mosquitto_sub -t "edgeai/#" -v

# Publish a sample telemetry message
mosquitto_pub -t "edgeai/machine01/telemetry" -m '{"device_id":"machine01","timestamp":"2026-07-19T10:00:00Z","machine_state":"Healthy","vibration_rms":0.18,"dominant_frequency":120,"audio_level":0.42}'
```

## Production Notes
For a real deployment, enable authentication (`password_file`) and TLS (`cafile`/`certfile`/`keyfile`, port 8883) — see the commented-out lines in `mosquitto.conf`.
