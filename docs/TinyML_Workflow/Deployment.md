# TinyML Workflow — Deployment
On-device components: `model_data.h` (quantized model byte array), `labels.h` (class labels), `inference.cpp/.h` (thin MicroInterpreter wrapper). Input preprocessing happens upstream in `signal_processing/`; output interpretation (argmax → state) happens in `app/app_state_machine.cpp`.
See `firmware/ESP32` and `firmware/README.md`.
