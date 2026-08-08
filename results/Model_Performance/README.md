# Model Performance

Records training/evaluation results for the TinyML classifier: accuracy, loss curves, precision/recall/F1, and confusion matrix, produced by `tinyml/Model_Training/train.py`.

## What Goes Here
- `training_history.png` — accuracy/loss curves over epochs
- `confusion_matrix.png` — test-set confusion matrix
- `classification_report.txt` — precision/recall/F1 per class
- `RESULTS.md` — narrative summary of the above with the exact dataset/version used

## How to Generate
```bash
cd tinyml
python Feature_Extraction/extract_features.py
python Model_Training/train.py    # prints classification report + confusion matrix to stdout
```
Redirect or copy the printed output into `RESULTS.md`, and add plots via `matplotlib` (e.g. plotting `history.history["accuracy"]` / `history.history["loss"]` from `train.py`).

**Status:** Empty — no model has been trained against real data yet (see `tinyml/Model/README.md`). This repository intentionally avoids fabricating accuracy/loss numbers before they are actually measured.
