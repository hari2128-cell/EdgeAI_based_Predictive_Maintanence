# Dashboard Backend

Node/Express service that bridges MQTT to the frontend via WebSocket + REST.

## Responsibilities
- Subscribe to `edgeai/+/status`, `edgeai/+/telemetry`, `edgeai/+/alerts`, `edgeai/+/diagnostics`
- Validate and parse incoming JSON payloads (malformed payloads are logged and discarded)
- Maintain an in-memory latest-state cache per device
- Broadcast updates to connected frontend clients over WebSocket (`/ws`)
- Expose REST endpoints for initial state fetch

## API
| Method | Path | Description |
|---|---|---|
| GET | `/api/health` | Backend liveness check |
| GET | `/api/machines` | Latest state for all known machines |
| GET | `/api/machines/:id` | Latest state for one machine |
| WS | `/ws` | Live push of `status`/`telemetry`/`alerts`/`diagnostics` events |

## Setup
```bash
cp .env.example .env   # edit MQTT_BROKER_URL if not using localhost
npm install
npm start
```

## Planned
Persist history to `dashboard/database/` (SQLite) instead of in-memory-only state; REST endpoints for historical queries.
