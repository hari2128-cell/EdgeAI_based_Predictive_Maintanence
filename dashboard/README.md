# Dashboard

Live monitoring dashboard for the EdgeAI Predictive Maintenance system: displays current machine state, live telemetry, and recent alerts, sourced from MQTT.

## Structure
```
dashboard/
├── README.md
├── frontend/       # React + Vite + Tailwind + Recharts + WebSocket
├── backend/        # Node/Express bridge: MQTT -> WebSocket/REST -> frontend
├── mqtt_broker/     # Local Mosquitto broker config
└── database/         # SQLite schema (planned historical storage)
```

## Architecture
```
ESP32 --MQTT--> Broker --MQTT (subscribe)--> Backend --WebSocket--> Frontend --> User
```

The backend acts as an intermediary between the MQTT broker and the dashboard: it subscribes to `edgeai/+/telemetry`, `edgeai/+/status`, and `edgeai/+/alerts`, validates/transforms incoming payloads, and re-broadcasts them to connected frontend clients over WebSocket. It also exposes a small REST API for the frontend's initial state fetch.

> An alternative, simpler deployment could have the frontend subscribe to MQTT directly via `mqtt.js` over WebSockets (Mosquitto supports MQTT-over-WebSocket on port 9001). This repo uses the Node backend bridge instead, to enable future features (validation, history, auth) without touching the frontend.

## Running Locally

**1. Start an MQTT broker** (see `mqtt_broker/README.md`), or point at a cloud broker.

**2. Backend:**
```bash
cd backend
npm install
npm start
```

**3. Frontend:**
```bash
cd frontend
npm install
npm run dev
```

Open the printed local URL (default `http://localhost:5173`).

## Dashboard Components
| Component | Description |
|---|---|
| Machine Status Card | Current health classification (Healthy/Warning/Fault) with color coding |
| Live Telemetry | Vibration RMS, dominant frequency, audio level — updated in real time |
| Trend Chart | Recharts line chart of recent vibration RMS history |
| Alerts Panel | Recent Warning/Fault events with timestamp and severity |
| Connection Status | Backend connectivity indicator |

## Planned Features
- Historical data persistence (`database/`)
- Multi-machine fleet view
- Authentication
- Confidence-score visualization once the TinyML model reports it
