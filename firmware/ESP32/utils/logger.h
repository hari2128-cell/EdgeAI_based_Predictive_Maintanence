#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

namespace Logger {

inline void info(const char* tag, const String& msg) {
  Serial.printf("[INFO][%s] %s\n", tag, msg.c_str());
}
inline void warn(const char* tag, const String& msg) {
  Serial.printf("[WARN][%s] %s\n", tag, msg.c_str());
}
inline void error(const char* tag, const String& msg) {
  Serial.printf("[ERROR][%s] %s\n", tag, msg.c_str());
}

}  // namespace Logger

#endif // LOGGER_H
