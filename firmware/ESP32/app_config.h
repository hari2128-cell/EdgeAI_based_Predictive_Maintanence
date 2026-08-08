#ifndef APP_CONFIG_H
#define APP_CONFIG_H

// =====================================================================
// EdgeAI Predictive Maintenance — Global Configuration
// =====================================================================

// ---------------------- Pin Map ----------------------
constexpr int PIN_I2C_SDA        = 21;
constexpr int PIN_I2C_SCL        = 22;

constexpr int PIN_I2S_SD         = 32;
constexpr int PIN_I2S_SCK        = 33;
constexpr int PIN_I2S_WS         = 25;

constexpr int PIN_VIBRATION_ADC  = 34;

constexpr int PIN_LED_GREEN      = 27;   // Healthy
constexpr int PIN_LED_YELLOW     = 26;   // Warning
constexpr int PIN_LED_RED        = 14;   // Fault

constexpr int PIN_BUZZER         = 12;

// ---------------------- WiFi / MQTT ----------------------
// NOTE: For real deployments, move credentials out of source control
// (e.g. into a gitignored secrets.h) — kept here as placeholders.
constexpr char WIFI_SSID[]       = "YOUR_WIFI_SSID";
constexpr char WIFI_PASSWORD[]   = "YOUR_WIFI_PASSWORD";

constexpr char MQTT_BROKER[]     = "broker.local";
constexpr int  MQTT_PORT         = 1883;
constexpr char MQTT_CLIENT_ID[]  = "edgeai_machine01";
constexpr char DEVICE_ID[]       = "machine01";

constexpr char MQTT_TOPIC_STATUS[]      = "edgeai/machine01/status";
constexpr char MQTT_TOPIC_TELEMETRY[]   = "edgeai/machine01/telemetry";
constexpr char MQTT_TOPIC_ALERTS[]      = "edgeai/machine01/alerts";
constexpr char MQTT_TOPIC_DIAGNOSTICS[] = "edgeai/machine01/diagnostics";

// ---------------------- Signal Processing ----------------------
constexpr int   SAMPLE_RATE_HZ      = 1000;
constexpr int   WINDOW_SIZE         = 256;
constexpr int   FFT_SIZE            = 256;
constexpr float DC_ALPHA            = 0.98f;

// ---------------------- TinyML ----------------------
constexpr int   FEATURE_VECTOR_SIZE = 10;
constexpr int   NUM_CLASSES         = 3;
constexpr int   TENSOR_ARENA_SIZE   = 20 * 1024;

// ---------------------- Machine State Thresholds ----------------------
constexpr float VIBRATION_WARNING_THRESHOLD = 0.35f; // g (RMS)
constexpr float VIBRATION_FAULT_THRESHOLD   = 0.75f; // g (RMS)

// ---------------------- Timing ----------------------
constexpr unsigned long LOOP_INTERVAL_MS         = 500;
constexpr unsigned long MQTT_PUBLISH_INTERVAL_MS = 2000;
constexpr unsigned long WIFI_RETRY_INTERVAL_MS   = 5000;

#endif // APP_CONFIG_H
