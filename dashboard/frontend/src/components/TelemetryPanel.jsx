import React from "react";

function Metric({ label, value, unit }) {
  return (
    <div className="rounded-lg bg-slate-900 p-4 border border-slate-800">
      <p className="text-xs text-slate-500">{label}</p>
      <p className="text-lg font-semibold">
        {value !== undefined && value !== null ? value : "--"}
        {unit && <span className="text-sm text-slate-500 ml-1">{unit}</span>}
      </p>
    </div>
  );
}

export default function TelemetryPanel({ telemetry }) {
  return (
    <div className="grid grid-cols-2 gap-3">
      <Metric label="Vibration RMS" value={telemetry?.vibration_rms?.toFixed?.(3)} unit="g" />
      <Metric label="Dominant Frequency" value={telemetry?.dominant_frequency} unit="Hz" />
      <Metric label="Audio Level" value={telemetry?.audio_level?.toFixed?.(2)} />
      <Metric label="Device ID" value={telemetry?.device_id} />
    </div>
  );
}
