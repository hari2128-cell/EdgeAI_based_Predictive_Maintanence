# Database (Planned)

Historical telemetry storage — not yet wired into the backend, which currently keeps only an in-memory latest-state cache (`dashboard/backend/services/stateStore.js`).

## Planned Schema (SQLite)
```sql
CREATE TABLE telemetry (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  device_id TEXT NOT NULL,
  timestamp TEXT NOT NULL,
  machine_state TEXT NOT NULL,
  vibration_rms REAL,
  dominant_frequency REAL,
  audio_level REAL
);

CREATE TABLE alerts (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  device_id TEXT NOT NULL,
  timestamp TEXT NOT NULL,
  severity TEXT NOT NULL,
  message TEXT
);

CREATE INDEX idx_telemetry_device_time ON telemetry (device_id, timestamp);
CREATE INDEX idx_alerts_device_time ON alerts (device_id, timestamp);
```

## Integration Plan
Add a `services/dbService.js` to `dashboard/backend/` that writes every incoming MQTT message to these tables, and new REST endpoints (`GET /api/machines/:id/history?range=24h`) for the frontend's historical charts.

**Status:** Schema designed, not yet implemented.
