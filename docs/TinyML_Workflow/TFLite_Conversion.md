# TinyML Workflow — TensorFlow Lite Conversion
```
model.h5 → TFLiteConverter (+ post-training int8 quantization) → model.tflite →
xxd -i model.tflite → model_data.h (C byte array) → firmware/ESP32/tinyml/model_data.h
```
TensorFlow Lite Micro executes the converted graph without a filesystem or dynamic memory allocator, using a preallocated "tensor arena." Quantization (float32 → int8) reduces model size and speeds up inference.
See `tinyml/TensorFlow_Lite/convert_to_tflite.py`.
