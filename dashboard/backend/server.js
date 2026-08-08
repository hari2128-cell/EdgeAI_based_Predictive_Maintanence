/**
 * server.js
 *
 * EdgeAI Predictive Maintenance dashboard backend.
 * Subscribes to MQTT telemetry/status/alert topics, keeps an in-memory
 * latest-state cache per device, exposes it via REST, and re-broadcasts
 * updates to connected frontend clients over WebSocket.
 */

require("dotenv").config();
const express = require("express");
const cors = require("cors");
const http = require("http");
const { WebSocketServer } = require("ws");

const { connectMqtt } = require("./services/mqttService");
const { getState, updateState } = require("./services/stateStore");
const machinesRouter = require("./routes/machines");

const PORT = process.env.PORT || 4000;

const app = express();
app.use(cors());
app.use(express.json());
app.use("/api/machines", machinesRouter);

app.get("/api/health", (req, res) => res.json({ ok: true }));

const server = http.createServer(app);
const wss = new WebSocketServer({ server, path: "/ws" });

function broadcast(payload) {
  const message = JSON.stringify(payload);
  wss.clients.forEach((client) => {
    if (client.readyState === client.OPEN) client.send(message);
  });
}

wss.on("connection", (ws) => {
  ws.send(JSON.stringify({ type: "snapshot", data: getState() }));
});

connectMqtt((topicType, deviceId, payload) => {
  updateState(deviceId, topicType, payload);
  broadcast({ type: topicType, deviceId, data: payload });
});

server.listen(PORT, () => {
  console.log(`EdgeAI dashboard backend listening on port ${PORT}`);
});
