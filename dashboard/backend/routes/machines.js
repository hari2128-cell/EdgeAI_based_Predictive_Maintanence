/**
 * routes/machines.js
 *
 * REST API for the dashboard frontend's initial state fetch.
 * (Live updates are pushed over WebSocket by server.js.)
 */

const express = require("express");
const { getState, getDeviceState } = require("../services/stateStore");

const router = express.Router();

router.get("/", (req, res) => {
  res.json(getState());
});

router.get("/:id", (req, res) => {
  const device = getDeviceState(req.params.id);
  if (!device) return res.status(404).json({ error: "Unknown device" });
  res.json(device);
});

module.exports = router;
