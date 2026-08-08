#ifndef ACCELEROMETER_DRIVER_H
#define ACCELEROMETER_DRIVER_H

namespace Drivers {
namespace Accelerometer {

bool begin(int sdaPin, int sclPin);
bool readG(float* x, float* y, float* z);
bool isConnected();

}  // namespace Accelerometer
}  // namespace Drivers

#endif // ACCELEROMETER_DRIVER_H
