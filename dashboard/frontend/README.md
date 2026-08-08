# Dashboard Frontend

React + Vite + Tailwind CSS dashboard for live machine health monitoring.

## Stack
React 18, Vite, Tailwind CSS, Recharts (trend charts), native WebSocket (backend push) + `fetch` (initial REST snapshot).

## Setup
```bash
cp .env.example .env   # point at your backend if not localhost:4000
npm install
npm run dev
```

## Structure
```
src/
├── main.jsx               # React entry point
├── App.jsx                # Top-level layout, one section per known machine
├── useDashboardData.js     # REST snapshot + WebSocket live-update hook
├── index.css               # Tailwind directives
└── components/
    ├── StatusCard.jsx       # Current machine state (color-coded)
    ├── TelemetryPanel.jsx    # Live metric tiles
    ├── TrendChart.jsx         # Recharts vibration RMS trend line
    ├── AlertsList.jsx          # Recent Warning/Fault alerts
    └── ConnectionStatus.jsx     # Backend connectivity indicator
```

## Data Flow
1. On mount, `useDashboardData` fetches `GET /api/machines` for the initial snapshot.
2. It then opens a WebSocket to the backend (`/ws`) and merges incoming `status` / `telemetry` / `alerts` / `diagnostics` events into React state as they arrive.
3. A short rolling telemetry history (last 30 points) is kept per device for the trend chart.

## Planned
Historical range queries once `dashboard/database/` is implemented; multi-machine comparison view; authentication.
