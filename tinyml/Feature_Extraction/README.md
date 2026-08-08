# Feature Extraction

## Purpose
Converts raw/preprocessed sensor windows into the fixed-length feature vector used by both training (Python) and on-device inference (C++).

## Inputs
- `preprocess.py` — raw signal arrays (from `tinyml/Dataset/<Class>/*.csv`)
- `extract_features.py` — preprocessed windows

## Outputs
- `tinyml/Dataset/features.csv` — combined feature table with a `label` column, ready for `Model_Training/train.py`

## Dependencies
`numpy`, `pandas` (see `tinyml/requirements.txt`)

## Files
| File | Purpose |
|---|---|
| `preprocess.py` | DC removal, moving-average filtering, min-max normalization, windowing |
| `extract_features.py` | Time-domain + frequency-domain feature computation, dataset-wide extraction driver |

## Current Implementation Status
Implemented and runnable against any correctly-formatted dataset CSVs. Produces an empty/warning result until `tinyml/Dataset/<Class>/` folders are populated with recorded sessions.

## Planned Enhancements
Kurtosis, skewness, spectral entropy, zero-crossing rate (particularly useful for the audio channel).
