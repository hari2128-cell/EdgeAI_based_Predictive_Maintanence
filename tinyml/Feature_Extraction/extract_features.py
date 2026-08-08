"""
extract_features.py

Converts preprocessed signal windows into the fixed-length feature
vector consumed by the TinyML model. Feature order MUST match
firmware/ESP32/signal_processing/feature_extraction.h:

  [0] vibration_rms
  [1] vibration_peak
  [2] vibration_mean
  [3] vibration_variance
  [4] vibration_crest_factor
  [5] vibration_dominant_frequency
  [6] vibration_band_energy
  [7] audio_rms
  [8] audio_peak
  [9] audio_dominant_frequency

Usage:
    python extract_features.py
Reads all CSVs under tinyml/Dataset/<Healthy|Warning|Fault>/ and writes
a combined feature table to tinyml/Dataset/features.csv.
"""

import glob
import os

import numpy as np
import pandas as pd

from preprocess import preprocess_signal

SAMPLE_RATE_HZ = 1000
WINDOW_SIZE = 256
DATASET_DIR = os.path.join(os.path.dirname(__file__), "..", "Dataset")
OUTPUT_PATH = os.path.join(DATASET_DIR, "features.csv")

CLASSES = ["Healthy", "Warning", "Fault"]
FEATURE_NAMES = [
    "vibration_rms", "vibration_peak", "vibration_mean", "vibration_variance",
    "vibration_crest_factor", "vibration_dominant_frequency", "vibration_band_energy",
    "audio_rms", "audio_peak", "audio_dominant_frequency",
]


def compute_time_domain_features(signal: np.ndarray):
    rms = np.sqrt(np.mean(signal ** 2))
    peak = np.max(np.abs(signal))
    mean = np.mean(signal)
    variance = np.var(signal)
    crest_factor = peak / rms if rms > 1e-6 else 0.0
    return rms, peak, mean, variance, crest_factor


def compute_frequency_domain_features(signal: np.ndarray, sample_rate: int):
    spectrum = np.abs(np.fft.rfft(signal))
    freqs = np.fft.rfftfreq(len(signal), d=1.0 / sample_rate)
    dominant_idx = np.argmax(spectrum[1:]) + 1 if len(spectrum) > 1 else 0
    dominant_freq = freqs[dominant_idx] if len(freqs) > 0 else 0.0
    band_energy = float(np.sum(spectrum ** 2))
    return dominant_freq, band_energy


def extract_features_from_window(vibration_window: np.ndarray, audio_window: np.ndarray,
                                   sample_rate: int = SAMPLE_RATE_HZ):
    v_rms, v_peak, v_mean, v_var, v_crest = compute_time_domain_features(vibration_window)
    v_dom_freq, v_band_energy = compute_frequency_domain_features(vibration_window, sample_rate)

    a_rms, a_peak, _, _, _ = compute_time_domain_features(audio_window)
    a_dom_freq, _ = compute_frequency_domain_features(audio_window, sample_rate)

    return [v_rms, v_peak, v_mean, v_var, v_crest, v_dom_freq, v_band_energy,
            a_rms, a_peak, a_dom_freq]


def process_class(label: str):
    rows = []
    class_dir = os.path.join(DATASET_DIR, label)
    csv_files = glob.glob(os.path.join(class_dir, "*.csv"))

    if not csv_files:
        print(f"[WARN] No CSV files found for class '{label}' in {class_dir}")
        return rows

    for path in csv_files:
        df = pd.read_csv(path)
        if not {"accel_x", "audio_sample"}.issubset(df.columns):
            print(f"[WARN] Skipping {path}: missing expected columns")
            continue

        vib_signal = df["accel_x"].to_numpy(dtype=float)
        audio_signal = df["audio_sample"].to_numpy(dtype=float)

        vib_windows = preprocess_signal(vib_signal, window_size=WINDOW_SIZE)
        audio_windows = preprocess_signal(audio_signal, window_size=WINDOW_SIZE)

        for vw, aw in zip(vib_windows, audio_windows):
            features = extract_features_from_window(np.array(vw), np.array(aw))
            rows.append(features + [label])

    return rows


def main():
    all_rows = []
    for label in CLASSES:
        all_rows.extend(process_class(label))

    if not all_rows:
        print("[WARN] No feature rows generated. Populate tinyml/Dataset/<Class>/ with CSVs first.")
        return

    out_df = pd.DataFrame(all_rows, columns=FEATURE_NAMES + ["label"])
    out_df.to_csv(OUTPUT_PATH, index=False)
    print(f"Wrote {len(out_df)} feature rows to {OUTPUT_PATH}")


if __name__ == "__main__":
    main()
