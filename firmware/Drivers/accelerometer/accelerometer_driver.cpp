#include "accelerometer_driver.h"

#include <Wire.h>

// Reference implementation for an I2C MEMS accelerometer (e.g. ADXL345 /
// MPU6050-class). Replace ACCEL_I2C_ADDR and register map with your
// exact module's datasheet values.

namespace Drivers {
namespace Accelerometer {

namespace {
constexpr uint8_t ACCEL_I2C_ADDR = 0x53;
bool connected_ = false;
}

bool begin(int sdaPin, int sclPin) {
  Wire.begin(sdaPin, sclPin);
  Wire.beginTransmission(ACCEL_I2C_ADDR);
  connected_ = (Wire.endTransmission() == 0);
  return connected_;
}

bool readG(float* x, float* y, float* z) {
  if (!connected_) return false;
  // TODO: read raw registers and convert to g using the sensor's
  // datasheet-specified sensitivity/scale factor.
  *x = 0.0f;
  *y = 0.0f;
  *z = 0.0f;
  return true;
}

bool isConnected() { return connected_; }

}  // namespace Accelerometer
}  // namespace Drivers
