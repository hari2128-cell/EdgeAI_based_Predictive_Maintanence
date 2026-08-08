#ifndef OLED_UI_H
#define OLED_UI_H

namespace OledUI {

bool begin();
void showBootScreen();
void showInitializingScreen();
void showStatusScreen(const char* machineState, float vibrationRms,
                       float dominantFrequency, bool wifiConnected, bool mqttConnected);

}  // namespace OledUI

#endif // OLED_UI_H
