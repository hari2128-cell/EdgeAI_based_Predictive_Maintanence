# Signal Processing Validation

## Objective
Confirm the on-device (C++) signal processing pipeline produces results consistent with the offline Python reference implementation, since training-time and inference-time preprocessing must match for the TinyML model to generalize correctly.

## Method
1. Record a fixed test signal (or reuse a session from `tinyml/Dataset/`).
2. Run it through the Python pipeline (`tinyml/Feature_Extraction/preprocess.py` + `extract_features.py`).
3. Feed the same raw values through the on-device pipeline (`firmware/ESP32/signal_processing/`) via a serial debug dump.
4. Compare the resulting feature vectors (RMS, peak, dominant frequency, etc.) within an acceptable numerical tolerance.

## Notes
The current on-device FFT (`firmware/ESP32/signal_processing/fft.cpp`) is a reference O(n²) DFT implementation; the Python side uses `numpy.fft.rfft`. Both should agree closely on dominant frequency and band energy for a stationary test signal, but exact floating-point equality is not expected.

**Status:** Method defined; validation run pending real hardware output.
