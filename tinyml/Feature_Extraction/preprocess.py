"""
preprocess.py

Signal preprocessing shared by the offline (Python) training pipeline.
Mirrors the on-device pipeline in firmware/ESP32/signal_processing/
(filters.h, normalization.h) so that training-time and inference-time
preprocessing stay consistent.

Pipeline: DC removal -> moving-average filtering -> min-max normalization
-> fixed-size windowing.
"""

import numpy as np


def remove_dc(signal: np.ndarray) -> np.ndarray:
    """Removes the DC offset (mean) from a 1D signal."""
    return signal - np.mean(signal)


def moving_average_filter(signal: np.ndarray, window: int = 5) -> np.ndarray:
    """Simple moving-average low-pass filter."""
    if window <= 1:
        return signal
    kernel = np.ones(window) / window
    return np.convolve(signal, kernel, mode="same")


def min_max_normalize(signal: np.ndarray) -> np.ndarray:
    """Normalizes a signal to the [-1, 1] range."""
    min_val, max_val = np.min(signal), np.max(signal)
    rng = max_val - min_val
    if rng < 1e-6:
        rng = 1e-6
    return 2.0 * ((signal - min_val) / rng) - 1.0


def window_signal(signal: np.ndarray, window_size: int = 256, overlap: int = 0):
    """Yields fixed-size (optionally overlapping) windows from a 1D signal."""
    step = window_size - overlap
    if step <= 0:
        raise ValueError("overlap must be smaller than window_size")
    for start in range(0, len(signal) - window_size + 1, step):
        yield signal[start:start + window_size]


def preprocess_signal(signal: np.ndarray, filter_window: int = 5,
                       window_size: int = 256, overlap: int = 0):
    """Full preprocessing pipeline: DC removal -> filter -> normalize -> window."""
    cleaned = remove_dc(signal)
    filtered = moving_average_filter(cleaned, filter_window)
    normalized = min_max_normalize(filtered)
    return list(window_signal(normalized, window_size, overlap))


if __name__ == "__main__":
    t = np.linspace(0, 1, 1000)
    synthetic = 0.5 * np.sin(2 * np.pi * 50 * t) + np.random.normal(0, 0.05, size=t.shape) + 2.0
    windows = preprocess_signal(synthetic, window_size=256)
    print(f"Generated {len(windows)} windows of size {len(windows[0]) if windows else 0}")
