import React from "react";
import { LineChart, Line, XAxis, YAxis, CartesianGrid, Tooltip, ResponsiveContainer } from "recharts";

export default function TrendChart({ data }) {
  if (!data || data.length === 0) {
    return <div className="text-sm text-slate-500 p-6 text-center">No telemetry history yet</div>;
  }

  return (
    <ResponsiveContainer width="100%" height={220}>
      <LineChart data={data}>
        <CartesianGrid strokeDasharray="3 3" stroke="#1e293b" />
        <XAxis dataKey="time" stroke="#64748b" fontSize={10} />
        <YAxis stroke="#64748b" fontSize={10} />
        <Tooltip contentStyle={{ background: "#0f172a", border: "1px solid #1e293b" }} />
        <Line type="monotone" dataKey="vibration_rms" stroke="#38bdf8" strokeWidth={2} dot={false} name="Vibration RMS (g)" />
      </LineChart>
    </ResponsiveContainer>
  );
}
