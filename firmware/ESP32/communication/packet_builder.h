#ifndef PACKET_BUILDER_H
#define PACKET_BUILDER_H

#include <Arduino.h>

#include "../signal_processing/feature_extraction.h"

namespace PacketBuilder {

String buildTelemetryPayload(const char* machineState,
                              const FeatureExtraction::FeatureVector& features);
String buildAlertPayload(const char* severity, const char* message);
String buildStatusPayload(bool wifiConnected, bool mqttConnected,
                           unsigned long uptimeSeconds);

}  // namespace PacketBuilder

#endif // PACKET_BUILDER_H
