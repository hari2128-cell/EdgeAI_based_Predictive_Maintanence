# TinyML Workflow — Preprocessing
Raw samples are cleaned before feature extraction: (1) DC offset removal, (2) noise filtering (moving average), (3) normalization, (4) windowing (fixed-length segments, e.g. 256 samples).

Implemented in Python for offline dataset preparation (`tinyml/Feature_Extraction/preprocess.py`) and mirrored in C++ on-device (`firmware/ESP32/signal_processing`) so that training-time and inference-time preprocessing stay consistent.
