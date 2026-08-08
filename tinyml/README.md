# TinyML Pipeline

End-to-end machine learning pipeline for on-device machine health classification: dataset → preprocessing → feature engineering → training → evaluation → TensorFlow Lite conversion → ESP32 deployment.

## Folder Structure
```
tinyml/
├── README.md
├── requirements.txt
├── Dataset/
│   ├── Healthy/
│   ├── Warning/
│   └── Fault/
├── Data_Collection/       # Firmware-side + host-side logging scripts
├── Feature_Extraction/    # Preprocessing + feature engineering (Python)
├── Model_Training/        # Model definition + training script
├── TensorFlow_Lite/       # .tflite conversion + C array export
└── Model/                 # Trained model artifacts (.h5, .tflite, model_data.h)
```

## Workflow
```
Dataset (Dataset/Healthy|Warning|Fault)
        │
        ▼
Feature_Extraction/preprocess.py + extract_features.py
        │
        ▼
Model_Training/train.py  →  Model/model.h5
        │
        ▼
TensorFlow_Lite/convert_to_tflite.py  →  Model/model.tflite, Model/model_data.h
        │
        ▼
firmware/ESP32/tinyml/model_data.h  (copy from Model/)
```

## Quick Start
```bash
pip install -r requirements.txt

# 1. Extract features from raw dataset CSVs
python Feature_Extraction/extract_features.py

# 2. Train the model
python Model_Training/train.py

# 3. Convert to TensorFlow Lite + generate C array
python TensorFlow_Lite/convert_to_tflite.py
```

## Dataset
Organized by machine state:
- `Dataset/Healthy/` — normal vibration amplitude, stable acoustic profile, normal operating frequency
- `Dataset/Warning/` — slight vibration increase, minor frequency deviation, early anomaly
- `Dataset/Fault/` — high vibration, abnormal acoustic signature

Each `.csv` file contains raw or windowed vibration + audio samples with a ground-truth label. See each per-class README for the exact schema.

## Model
A compact multilayer perceptron (MLP) is used as the baseline, taking the 10-value engineered feature vector (see `firmware/ESP32/signal_processing/feature_extraction.h`) as input and outputting 3 class scores (Healthy / Warning / Fault). Chosen over a 1D-CNN because the model consumes hand-engineered features rather than raw time-series.

## Status
| Stage | Status |
|---|---|
| Dataset schema & folder structure | Implemented |
| Feature extraction pipeline | Implemented |
| Baseline MLP training script | Implemented |
| TFLite conversion + quantization | Implemented |
| Trained model artifacts (actual weights) | Pending — run the pipeline against a populated dataset |
| Confidence-score reporting | Planned |
| Multi-class fault sub-typing | Planned |

Each subfolder contains its own `README.md` describing purpose, inputs, outputs, dependencies, and status.
