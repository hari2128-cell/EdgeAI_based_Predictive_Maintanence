# TinyML Workflow

End-to-end AI pipeline for the EdgeAI Predictive Maintenance system.

```
Data Collection → Data Preprocessing → Feature Engineering → Model Selection →
Training → Validation → Quantization → TensorFlow Lite Conversion →
ESP32 Deployment → Runtime Inference
```

1. **Data Collection** — vibration + acoustic samples recorded per machine state (Healthy / Warning / Fault). See `tinyml/Data_Collection/`.
2. **Preprocessing** — DC removal, filtering, normalization, windowing. See `tinyml/Feature_Extraction/`.
3. **Feature Engineering** — RMS, peak, crest factor, dominant frequency, frequency-band energy, etc.
4. **Model Selection** — a compact MLP sized to fit ESP32 memory/latency budgets.
5. **Training** — see `tinyml/Model_Training/train.py`.
6. **Validation** — accuracy, precision, recall, F1, confusion matrix on a held-out test split.
7. **Quantization** — post-training int8 quantization to shrink model size and speed up inference.
8. **TensorFlow Lite Conversion** — `.h5` → `.tflite` → C byte array (`model_data.h`).
9. **ESP32 Deployment** — `firmware/ESP32` includes `model_data.h` and runs inference via TensorFlow Lite Micro.
10. **Runtime Inference** — feature vector → interpreter.Invoke() → output tensor → machine state.

See `tinyml/README.md` and `docs/TinyML_Workflow/` for module-level detail.
