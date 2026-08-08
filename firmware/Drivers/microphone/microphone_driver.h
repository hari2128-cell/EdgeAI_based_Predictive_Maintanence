#ifndef MICROPHONE_DRIVER_H
#define MICROPHONE_DRIVER_H

#include <cstdint>

namespace Drivers {
namespace Microphone {

bool begin(int sdPin, int sckPin, int wsPin, int sampleRateHz);
int readSamples(int32_t* buffer, int maxSamples);

}  // namespace Microphone
}  // namespace Drivers

#endif // MICROPHONE_DRIVER_H
