# Literature Review

## Predictive Maintenance Concepts
Predictive maintenance (PdM) uses real-time condition data to schedule maintenance only when needed, reducing both unplanned downtime (associated with reactive maintenance) and unnecessary servicing (associated with time-based preventive maintenance).

## Condition Monitoring Techniques
Vibration analysis is one of the most established condition-monitoring techniques for rotating machinery, since mechanical defects (bearing wear, imbalance, misalignment) produce characteristic changes in vibration amplitude and frequency content. Acoustic emission monitoring is increasingly used as a complementary, often earlier-warning, signal source.

## TinyML in Embedded Systems
TinyML refers to running machine learning inference on microcontroller-class hardware (kilobytes of RAM, no OS or a lightweight RTOS). TensorFlow Lite for Microcontrollers is a widely used runtime enabling quantized neural network inference on devices such as the ESP32 and Arm Cortex-M series, without requiring an external accelerator.

## Edge AI Trends
Edge AI moves inference away from centralized cloud servers toward the data source, reducing latency, bandwidth usage, and dependency on network connectivity — properties that are especially valuable in industrial environments where network access may be limited or unreliable.

## Industrial IoT Architectures
Industrial IoT (IIoT) systems commonly use lightweight publish-subscribe protocols such as MQTT to connect distributed sensing nodes to centralized dashboards or historians, favoring low bandwidth usage and scalability to many devices.

## References
See [`References.md`](References.md) for a consolidated reference list.
