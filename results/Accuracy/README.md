# Accuracy

Focused accuracy metrics and per-class breakdowns, complementing the fuller training report in `results/Model_Performance/`.

## What Goes Here
- Overall test accuracy
- Per-class accuracy / recall (how often each of Healthy/Warning/Fault is correctly identified)
- Any threshold-classifier-vs-TinyML-model accuracy comparison (the firmware's fallback threshold classifier in `firmware/ESP32/tinyml/inference.cpp` vs. the trained model)

**Status:** Empty — populate once `tinyml/Model_Training/train.py` has been run against a real, populated dataset.
