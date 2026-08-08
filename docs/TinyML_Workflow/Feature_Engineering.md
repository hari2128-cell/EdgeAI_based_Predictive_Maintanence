# TinyML Workflow — Feature Engineering
Each preprocessed window is reduced to a fixed-length feature vector:

**Time domain:** RMS, Peak, Mean, Variance, Crest Factor
**Frequency domain (via FFT):** Dominant Frequency, Frequency Band Energy, Spectral Peaks

Planned additions: Kurtosis, Skewness, Spectral Entropy, Zero-Crossing Rate.
See `tinyml/Feature_Extraction/extract_features.py`.
