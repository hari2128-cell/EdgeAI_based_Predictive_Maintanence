#ifndef ACOUSTIC_SENSOR_H
#define ACOUSTIC_SENSOR_H

// Hardware-independent acoustic sensing interface, wrapping the I2S
// microphone driver.
namespace AcousticSensor {

bool begin();
int readWindow(float* outBuffer, int count);
bool isAvailable();

}  // namespace AcousticSensor

#endif // ACOUSTIC_SENSOR_H
