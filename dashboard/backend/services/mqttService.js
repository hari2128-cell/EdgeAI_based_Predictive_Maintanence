/**
 * mqttService.js
 *
 * Connects to the MQTT broker and subscribes to all EdgeAI machine
 * topics, parsing incoming payloads and invoking a callback with a
 * normalized (topicType, deviceId, payload) tuple.
 *
 * Topic pattern: edgeai/<machine_id>/<status|telemetry|alerts|diagnostics>
 */

const mqtt = require("mqtt");

function connectMqtt(onMessage) {
  const brokerUrl = process.env.MQTT_BROKER_URL || "mqtt://localhost:1883";
  const options = {};
  if (process.env.MQTT_USERNAME) {
    options.username = process.env.MQTT_USERNAME;
    options.password = process.env.MQTT_PASSWORD;
  }

  const client = mqtt.connect(brokerUrl, options);

  client.on("connect", () => {
    console.log(`Connected to MQTT broker at ${brokerUrl}`);
    client.subscribe("edgeai/+/status");
    client.subscribe("edgeai/+/telemetry");
    client.subscribe("edgeai/+/alerts");
    client.subscribe("edgeai/+/diagnostics");
  });

  client.on("reconnect", () => console.warn("Reconnecting to MQTT broker..."));
  client.on("error", (err) => console.error("MQTT error:", err.message));

  client.on("message", (topic, messageBuffer) => {
    const parts = topic.split("/");
    if (parts.length !== 3 || parts[0] !== "edgeai") return;
    const deviceId = parts[1];
    const topicType = parts[2];

    let payload;
    try {
      payload = JSON.parse(messageBuffer.toString());
    } catch (err) {
      console.warn(`Discarding malformed payload on ${topic}:`, err.message);
      return;
    }

    onMessage(topicType, deviceId, payload);
  });

  return client;
}

module.exports = { connectMqtt };
