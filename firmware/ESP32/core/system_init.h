#ifndef SYSTEM_INIT_H
#define SYSTEM_INIT_H

// Handles one-time hardware/peripheral bring-up: GPIO configuration,
// I2C/I2S bus setup. Application code should call SystemInit::begin()
// once from setup() and never touch hardware registers directly.
namespace SystemInit {

// Returns true if all critical peripherals initialized successfully.
bool begin();

}  // namespace SystemInit

#endif // SYSTEM_INIT_H
