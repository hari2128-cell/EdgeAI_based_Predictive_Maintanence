#include "app_controller.h"

#include "../alarms/buzzer_alarm.h"
#include "../alarms/led_status.h"
#include "../alarms/notifier.h"
#include "../app_config.h"
#include "../communication/mqtt_manager.h"
#include "../communication/packet_builder.h"
#include "../communication/wifi_manager.h"
#include "../core/diagnostics.h"
#include "../display/oled_ui.h"
#include "../sensors/acoustic.h"
#include "../sensors/vibration.h"
#include "../signal_processing/feature_extraction.h"
#include "../signal_processing/fft.h"
#include "../signal_processing/filters.h"
#include "../signal_processing/normalization.h"
#include "../tinyml/inference.h"
#include "../utils/logger.h"
#include "../utils/timer.h"
#include "app_state_machine.h"

namespace AppController {

namespace {

AppStateMachine stateMachine;
IntervalTimer loopTimer(LOOP_INTERVAL_MS);
IntervalTimer publishTimer(MQTT_PUBLISH_INTERVAL_MS);

float vibrationBuffer[WINDOW_SIZE];
float vibrationFiltered[WINDOW_SIZE];
float fftReal[FFT_SIZE];
float fftImag[FFT_SIZE];
float fftMagnitude[FFT_SIZE / 2];

FeatureExtraction::FeatureVector lastFeatures;
float lastScores[NUM_CLASSES];

}  // namespace

void begin() {
  Diagnostics::logBoot("Starting AppController...");

  OledUI::begin();
  OledUI::showBootScreen();

  bool vibOk = VibrationSensor::begin();
  bool audioOk = AcousticSensor::begin();
  Diagnostics::logSensorStatus("Vibration", vibOk);
  Diagnostics::logSensorStatus("Acoustic", audioOk);

  WiFiManager::begin();
  MqttManager::begin();

  Inference::begin();  // Falls back to threshold classifier if no model present

  Notifier::begin();
  stateMachine.begin();

  OledUI::showInitializingScreen();
  Diagnostics::logBoot("AppController ready");
}

void loop() {
  WiFiManager::loop();
  MqttManager::loop();

  if (!loopTimer.ready()) return;

  // 1. Acquire
  Filters::DCRemover dcRemover(DC_ALPHA);
  int samplesRead = VibrationSensor::readWindow(vibrationBuffer, WINDOW_SIZE);
  if (samplesRead < WINDOW_SIZE) {
    Diagnostics::logError("AppController", "Incomplete vibration window - skipping cycle");
    return;
  }

  // 2. Preprocess: DC removal + normalization
  for (int i = 0; i < WINDOW_SIZE; i++) {
    vibrationFiltered[i] = dcRemover.process(vibrationBuffer[i]);
  }
  Normalization::minMaxNormalize(vibrationFiltered, WINDOW_SIZE);

  // 3. FFT
  for (int i = 0; i < FFT_SIZE; i++) {
    fftReal[i] = vibrationFiltered[i];
    fftImag[i] = 0.0f;
  }
  FFTProcessor::computeMagnitudeSpectrum(fftReal, fftImag, FFT_SIZE, SAMPLE_RATE_HZ, fftMagnitude);

  // 4. Feature extraction
  lastFeatures = FeatureExtraction::extractVibrationFeatures(
      vibrationFiltered, WINDOW_SIZE, fftMagnitude, FFT_SIZE / 2, SAMPLE_RATE_HZ);

  // 5. TinyML inference (or threshold fallback)
  int predictedClass = Inference::classify(lastFeatures, lastScores);
  if (predictedClass < 0) {
    Diagnostics::logError("AppController", "Inference failed - retaining last state");
    predictedClass = 0;
  }

  // 6. State machine (debounced)
  bool changed = stateMachine.update(predictedClass);
  if (changed) {
    Notifier::onStateChanged(stateMachine.currentState());
  }

  // 7. Update display every cycle
  OledUI::showStatusScreen(stateMachine.currentStateName(), lastFeatures.values[0],
                            lastFeatures.values[5], WiFiManager::isConnected(),
                            MqttManager::isConnected());

  // 8. Publish telemetry on its own (slower) interval
  if (publishTimer.ready()) {
    String payload = PacketBuilder::buildTelemetryPayload(stateMachine.currentStateName(), lastFeatures);
    if (!MqttManager::publishTelemetry(payload)) {
      Diagnostics::logError("AppController", "Telemetry publish skipped (MQTT unavailable)");
    }
  }
}

}  // namespace AppController
