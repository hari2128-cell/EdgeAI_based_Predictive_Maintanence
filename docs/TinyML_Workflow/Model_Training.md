# TinyML Workflow — Model Training
A compact multilayer perceptron (MLP) is used as the baseline classifier, chosen for its small memory footprint and fast inference on ESP32 given the fixed-length hand-engineered feature vector input.

**Pipeline:** Dataset → Preprocessing → Feature Engineering → Train/Val/Test Split → Model Training → Evaluation → Export.
See `tinyml/Model_Training/train.py` and `README.md` for split ratios, loss function, optimizer, and evaluation metrics.
