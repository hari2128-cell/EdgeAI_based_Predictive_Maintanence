#include "microphone_driver.h"

#include <driver/i2s.h>

namespace Drivers {
namespace Microphone {

namespace {
constexpr i2s_port_t I2S_PORT = I2S_NUM_0;
}

bool begin(int sdPin, int sckPin, int wsPin, int sampleRateHz) {
  i2s_config_t i2sConfig = {
      .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
      .sample_rate = (uint32_t)sampleRateHz,
      .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
      .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
      .communication_format = I2S_COMM_FORMAT_STAND_I2S,
      .intr_alloc_flags = 0,
      .dma_buf_count = 4,
      .dma_buf_len = 256,
      .use_apll = false,
  };

  i2s_pin_config_t pinConfig = {
      .bck_io_num = sckPin,
      .ws_io_num = wsPin,
      .data_out_num = I2S_PIN_NO_CHANGE,
      .data_in_num = sdPin,
  };

  if (i2s_driver_install(I2S_PORT, &i2sConfig, 0, nullptr) != ESP_OK) return false;
  if (i2s_set_pin(I2S_PORT, &pinConfig) != ESP_OK) return false;
  return true;
}

int readSamples(int32_t* buffer, int maxSamples) {
  size_t bytesRead = 0;
  i2s_read(I2S_PORT, buffer, maxSamples * sizeof(int32_t), &bytesRead, portMAX_DELAY);
  return bytesRead / sizeof(int32_t);
}

}  // namespace Microphone
}  // namespace Drivers
