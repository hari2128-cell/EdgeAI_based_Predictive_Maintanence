/**
 * stateStore.js
 *
 * Simple in-memory latest-state cache, keyed by device ID. Not a
 * historical store (that is planned — see dashboard/database/).
 */

const state = {};

function ensureDevice(deviceId) {
  if (!state[deviceId]) {
    state[deviceId] = { status: null, telemetry: null, alerts: [], diagnostics: null };
  }
  return state[deviceId];
}

function updateState(deviceId, topicType, payload) {
  const device = ensureDevice(deviceId);
  if (topicType === "alerts") {
    device.alerts.unshift({ ...payload, receivedAt: new Date().toISOString() });
    device.alerts = device.alerts.slice(0, 50);
  } else {
    device[topicType] = payload;
  }
}

function getState() {
  return state;
}

function getDeviceState(deviceId) {
  return state[deviceId] || null;
}

module.exports = { updateState, getState, getDeviceState };
