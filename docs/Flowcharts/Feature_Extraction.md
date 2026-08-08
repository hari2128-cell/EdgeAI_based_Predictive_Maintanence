# Feature Extraction Flowchart

```
Windowed Signal → DC Offset Removal → Filtering → Normalization →
Time-Domain Features (RMS, Peak, Mean, Variance, Crest Factor) →
FFT → Frequency-Domain Features (Dominant Frequency, Band Energy, Spectral Peaks) →
Feature Vector
```

Time-domain and frequency-domain features are concatenated into a single fixed-length feature vector, which is the input to the TinyML model.
