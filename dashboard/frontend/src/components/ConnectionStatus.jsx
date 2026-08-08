import React from "react";

export default function ConnectionStatus({ connected }) {
  return (
    <div className="flex items-center gap-2 text-sm">
      <span className={`h-2 w-2 rounded-full ${connected ? "bg-healthy" : "bg-fault"}`} />
      <span className="text-slate-400">{connected ? "Backend connected" : "Backend disconnected"}</span>
    </div>
  );
}
