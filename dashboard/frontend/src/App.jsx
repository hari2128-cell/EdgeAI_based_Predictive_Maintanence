import React from "react";
import { useDashboardData } from "./useDashboardData.js";
import StatusCard from "./components/StatusCard.jsx";
import TelemetryPanel from "./components/TelemetryPanel.jsx";
import TrendChart from "./components/TrendChart.jsx";
import AlertsList from "./components/AlertsList.jsx";
import ConnectionStatus from "./components/ConnectionStatus.jsx";

export default function App() {
  const { machines, connected, history } = useDashboardData();
  const deviceIds = Object.keys(machines);

  return (
    <div className="min-h-screen bg-slate-950 text-slate-100">
      <header className="border-b border-slate-800 px-6 py-4 flex items-center justify-between">
        <div>
          <h1 className="text-lg font-bold">EdgeAI Predictive Maintenance</h1>
          <p className="text-xs text-slate-500">Real-time machine health dashboard</p>
        </div>
        <ConnectionStatus connected={connected} />
      </header>

      <main className="p-6 space-y-8">
        {deviceIds.length === 0 && (
          <div className="text-center text-slate-500 py-20">
            Waiting for telemetry from a machine... (publish to{" "}
            <code className="text-slate-300">edgeai/&lt;machine_id&gt;/telemetry</code>)
          </div>
        )}

        {deviceIds.map((deviceId) => {
          const device = machines[deviceId];
          return (
            <section key={deviceId} className="grid grid-cols-1 lg:grid-cols-3 gap-6">
              <StatusCard deviceId={deviceId} telemetry={device.telemetry} />

              <div className="lg:col-span-2 grid grid-cols-1 md:grid-cols-2 gap-6">
                <div className="rounded-xl border border-slate-800 p-4">
                  <h3 className="text-sm font-semibold mb-3 text-slate-300">Live Telemetry</h3>
                  <TelemetryPanel telemetry={device.telemetry} />
                </div>

                <div className="rounded-xl border border-slate-800 p-4">
                  <h3 className="text-sm font-semibold mb-3 text-slate-300">Vibration RMS Trend</h3>
                  <TrendChart data={history[deviceId]} />
                </div>

                <div className="rounded-xl border border-slate-800 p-4 md:col-span-2">
                  <h3 className="text-sm font-semibold mb-1 text-slate-300">Recent Alerts</h3>
                  <AlertsList alerts={device.alerts} />
                </div>
              </div>
            </section>
          );
        })}
      </main>
    </div>
  );
}
