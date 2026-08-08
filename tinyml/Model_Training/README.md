# Model Training

## Purpose
Trains the machine-health classifier on the engineered feature table.

## Inputs
`tinyml/Dataset/features.csv` (produced by `Feature_Extraction/extract_features.py`)

## Outputs
- `tinyml/Model/model.h5` — trained Keras model
- `tinyml/Model/scaler_stats.npz` — feature scaler mean/scale + class label order

## Model Architecture
Compact MLP: `Input(10) -> Dense(16, relu) -> Dense(8, relu) -> Dense(3, softmax)`.

Chosen over a 1D-CNN because the model consumes hand-engineered features (not raw time-series), for which a small dense network is sufficient and keeps the resulting `.tflite` file well within ESP32 memory budgets.

## Training Configuration
| Parameter | Value |
|---|---|
| Train / Val / Test split | ~72% / 13% / 15% (stratified) |
| Loss | Sparse categorical crossentropy |
| Optimizer | Adam (lr=1e-3) |
| Epochs | Up to 100, with early stopping (patience=10 on val_loss) |
| Batch size | 16 |

## Evaluation Metrics
Accuracy, precision, recall, F1-score (via `sklearn.metrics.classification_report`), and a confusion matrix are printed at the end of training and should be recorded in `results/Model_Performance/` once a real dataset is available.

## Dependencies
`tensorflow`, `scikit-learn`, `numpy`, `pandas` (see `tinyml/requirements.txt`)

## Current Implementation Status
Training script is complete and runnable. Actual accuracy/loss numbers are not fabricated here — they will be populated in `results/Model_Performance/` after running against real recorded data.

## Planned Enhancements
Hyperparameter tuning (grid/random search over hidden layer sizes), k-fold cross-validation for small datasets, class-weighting if the dataset is imbalanced.
