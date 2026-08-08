#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

#include <Arduino.h>

namespace Diagnostics {

void logBoot(const String& message);
void logError(const String& module, const String& message);
void logSensorStatus(const String& sensorName, bool ok);
void logNetworkStatus(bool wifiConnected, bool mqttConnected);

}  // namespace Diagnostics

#endif // DIAGNOSTICS_H
