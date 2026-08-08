import React from "react";

const STATE_STYLES = {
  Healthy: { bg: "bg-healthy/10", border: "border-healthy", text: "text-healthy", dot: "bg-healthy" },
  Warning: { bg: "bg-warning/10", border: "border-warning", text: "text-warning", dot: "bg-warning" },
  Fault: { bg: "bg-fault/10", border: "border-fault", text: "text-fault", dot: "bg-fault" },
};

export default function StatusCard({ deviceId, telemetry }) {
  const state = telemetry?.machine_state || "Unknown";
  const style = STATE_STYLES[state] || { bg: "bg-slate-800", border: "border-slate-700", text: "text-slate-300", dot: "bg-slate-500" };

  return (
    <div className={`rounded-xl border ${style.border} ${style.bg} p-6`}>
      <div className="flex items-center justify-between">
        <div>
          <p className="text-sm text-slate-400">Machine</p>
          <h2 className="text-xl font-semibold">{deviceId}</h2>
        </div>
        <span className={`h-3 w-3 rounded-full ${style.dot} animate-pulse`} />
      </div>

      <p className={`mt-4 text-3xl font-bold ${style.text}`}>{state}</p>
      <p className="mt-1 text-xs text-slate-500">
        {telemetry?.timestamp ? `Last update: ${telemetry.timestamp}` : "No telemetry yet"}
      </p>
    </div>
  );
}
