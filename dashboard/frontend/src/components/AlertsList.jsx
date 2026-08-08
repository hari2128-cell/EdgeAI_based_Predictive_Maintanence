import React from "react";

const SEVERITY_COLOR = {
  Fault: "text-fault",
  Warning: "text-warning",
};

export default function AlertsList({ alerts = [] }) {
  if (alerts.length === 0) {
    return <p className="text-sm text-slate-500 p-4 text-center">No recent alerts</p>;
  }

  return (
    <ul className="divide-y divide-slate-800">
      {alerts.map((alert, idx) => (
        <li key={idx} className="py-3 flex items-start justify-between gap-4">
          <div>
            <p className={`font-medium ${SEVERITY_COLOR[alert.severity] || "text-slate-200"}`}>
              {alert.severity || "Alert"}
            </p>
            <p className="text-sm text-slate-400">{alert.message}</p>
          </div>
          <span className="text-xs text-slate-600 whitespace-nowrap">
            {alert.receivedAt ? new Date(alert.receivedAt).toLocaleTimeString() : ""}
          </span>
        </li>
      ))}
    </ul>
  );
}
