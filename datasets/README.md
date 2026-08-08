# Datasets

General-purpose dataset staging area, distinct from `tinyml/Dataset/` (which is the exact folder consumed by the TinyML training pipeline). This folder tracks data provenance across the raw → processed → training-ready lifecycle.

```
datasets/
├── Raw/         # Unmodified sensor recordings, as captured
├── Processed/   # Cleaned/filtered signals (DC removal, filtering, normalization applied)
└── Training/    # Final feature-engineered tables ready for model training
```

## Data Provenance Flow
```
Raw/ (as recorded) → Processed/ (tinyml/Feature_Extraction/preprocess.py) → Training/ (tinyml/Feature_Extraction/extract_features.py output)
```

`tinyml/Dataset/<Healthy|Warning|Fault>/` mirrors `datasets/Raw/` organized by class label for direct pipeline consumption; this top-level `datasets/` folder is kept for a lifecycle-stage view (raw vs. processed vs. training-ready) useful for data provenance tracking and auditing.

**Status:** No data recorded yet — see `tinyml/Data_Collection/` for the logging workflow.
