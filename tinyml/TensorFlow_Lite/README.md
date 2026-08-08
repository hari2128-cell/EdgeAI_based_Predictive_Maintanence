# TensorFlow Lite Conversion

## Purpose
Converts the trained Keras model into a quantized `.tflite` model and exports it as a C byte array for ESP32 deployment.

## Pipeline
```
model.h5 -> TFLiteConverter (+ post-training int8 quantization) -> model.tflite -> model_data.h (C array)
```

## Inputs
`tinyml/Model/model.h5` (from `Model_Training/train.py`)

## Outputs
- `tinyml/Model/model.tflite`
- `tinyml/Model/model_data.h` — copy into `firmware/ESP32/tinyml/model_data.h`

## Why Quantization?
Post-training int8 quantization typically shrinks model size ~4x and speeds up inference on the ESP32's integer-optimized paths, at a small (and measurable, once real data is available) accuracy cost — an acceptable trade-off given the ESP32's constrained Flash/RAM budget.

## Dependencies
`tensorflow` (see `tinyml/requirements.txt`)

## Current Implementation Status
Script is complete and runnable once `model.h5` exists. The representative dataset generator currently uses random samples for calibration as a placeholder — swap in real (scaled) validation data for production-quality quantization.
