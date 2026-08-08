import { useEffect, useRef, useState } from "react";

const API_BASE_URL = import.meta.env.VITE_API_BASE_URL || "http://localhost:4000";
const WS_URL = import.meta.env.VITE_WS_URL || "ws://localhost:4000/ws";

/**
 * useDashboardData
 *
 * Fetches the initial machine state snapshot over REST, then subscribes
 * to live updates over WebSocket, merging them into a single state map
 * keyed by device ID. Also keeps a short rolling history of telemetry
 * per device for trend charts.
 */
export function useDashboardData() {
  const [machines, setMachines] = useState({});
  const [connected, setConnected] = useState(false);
  const historyRef = useRef({});

  useEffect(() => {
    fetch(`${API_BASE_URL}/api/machines`)
      .then((res) => res.json())
      .then((data) => setMachines(data))
      .catch((err) => console.error("Failed to fetch initial machine state:", err));

    const ws = new WebSocket(WS_URL);

    ws.onopen = () => setConnected(true);
    ws.onclose = () => setConnected(false);
    ws.onerror = () => setConnected(false);

    ws.onmessage = (event) => {
      const msg = JSON.parse(event.data);

      if (msg.type === "snapshot") {
        setMachines(msg.data);
        return;
      }

      setMachines((prev) => {
        const deviceId = msg.deviceId;
        const existing = prev[deviceId] || { status: null, telemetry: null, alerts: [], diagnostics: null };

        if (msg.type === "alerts") {
          const alerts = [{ ...msg.data, receivedAt: new Date().toISOString() }, ...(existing.alerts || [])].slice(0, 50);
          return { ...prev, [deviceId]: { ...existing, alerts } };
        }

        if (msg.type === "telemetry") {
          const history = historyRef.current[deviceId] || [];
          historyRef.current[deviceId] = [
            ...history,
            {
              time: new Date().toLocaleTimeString(),
              vibration_rms: msg.data.vibration_rms,
              dominant_frequency: msg.data.dominant_frequency,
            },
          ].slice(-30);
        }

        return { ...prev, [deviceId]: { ...existing, [msg.type]: msg.data } };
      });
    };

    return () => ws.close();
  }, []);

  return { machines, connected, history: historyRef.current };
}
