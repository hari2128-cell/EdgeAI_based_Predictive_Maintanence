#ifndef VIBRATION_SENSOR_H
#define VIBRATION_SENSOR_H

// Hardware-independent vibration sensing interface. Wraps the
// accelerometer driver and provides calibrated samples to signal processing.
namespace VibrationSensor {

bool begin();
int readWindow(float* outBuffer, int count);
bool isAvailable();

}  // namespace VibrationSensor

#endif // VIBRATION_SENSOR_H
