"""
train.py

Trains a compact MLP classifier on the engineered feature table produced
by tinyml/Feature_Extraction/extract_features.py, evaluates it, and
exports the trained model for TensorFlow Lite conversion.

Usage:
    python train.py
"""

import os

import numpy as np
import pandas as pd
import tensorflow as tf
from sklearn.metrics import classification_report, confusion_matrix
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder, StandardScaler

FEATURES_CSV = os.path.join(os.path.dirname(__file__), "..", "Dataset", "features.csv")
MODEL_OUT_DIR = os.path.join(os.path.dirname(__file__), "..", "Model")
MODEL_OUT_PATH = os.path.join(MODEL_OUT_DIR, "model.h5")
SCALER_STATS_PATH = os.path.join(MODEL_OUT_DIR, "scaler_stats.npz")

RANDOM_SEED = 42
TEST_SIZE = 0.15
VAL_SIZE = 0.15
EPOCHS = 100
BATCH_SIZE = 16


def load_dataset():
    if not os.path.exists(FEATURES_CSV):
        raise FileNotFoundError(
            f"{FEATURES_CSV} not found. Run "
            "tinyml/Feature_Extraction/extract_features.py first, after "
            "populating tinyml/Dataset/<Class>/ with recorded sessions."
        )
    df = pd.read_csv(FEATURES_CSV)
    X = df.drop(columns=["label"]).to_numpy(dtype=np.float32)
    y_raw = df["label"].to_numpy()
    return X, y_raw


def build_model(input_dim: int, num_classes: int) -> tf.keras.Model:
    """Compact MLP sized for ESP32 deployment."""
    model = tf.keras.Sequential([
        tf.keras.layers.Input(shape=(input_dim,)),
        tf.keras.layers.Dense(16, activation="relu"),
        tf.keras.layers.Dense(8, activation="relu"),
        tf.keras.layers.Dense(num_classes, activation="softmax"),
    ])
    model.compile(
        optimizer=tf.keras.optimizers.Adam(learning_rate=1e-3),
        loss="sparse_categorical_crossentropy",
        metrics=["accuracy"],
    )
    return model


def main():
    os.makedirs(MODEL_OUT_DIR, exist_ok=True)

    X, y_raw = load_dataset()

    label_encoder = LabelEncoder()
    y = label_encoder.fit_transform(y_raw)
    print(f"Classes (in encoded order): {list(label_encoder.classes_)}")

    scaler = StandardScaler()
    X_scaled = scaler.fit_transform(X)

    X_train, X_test, y_train, y_test = train_test_split(
        X_scaled, y, test_size=TEST_SIZE, random_state=RANDOM_SEED, stratify=y
    )
    X_train, X_val, y_train, y_val = train_test_split(
        X_train, y_train, test_size=VAL_SIZE, random_state=RANDOM_SEED, stratify=y_train
    )

    model = build_model(input_dim=X.shape[1], num_classes=len(label_encoder.classes_))
    model.summary()

    early_stop = tf.keras.callbacks.EarlyStopping(
        monitor="val_loss", patience=10, restore_best_weights=True
    )

    model.fit(
        X_train, y_train,
        validation_data=(X_val, y_val),
        epochs=EPOCHS,
        batch_size=BATCH_SIZE,
        callbacks=[early_stop],
        verbose=2,
    )

    test_loss, test_acc = model.evaluate(X_test, y_test, verbose=0)
    print(f"\nTest accuracy: {test_acc:.4f} | Test loss: {test_loss:.4f}")

    y_pred = np.argmax(model.predict(X_test), axis=1)
    print("\nClassification report:")
    print(classification_report(y_test, y_pred, target_names=label_encoder.classes_))
    print("Confusion matrix:")
    print(confusion_matrix(y_test, y_pred))

    model.save(MODEL_OUT_PATH)
    np.savez(SCALER_STATS_PATH, mean=scaler.mean_, scale=scaler.scale_,
             classes=label_encoder.classes_)
    print(f"\nSaved trained model to {MODEL_OUT_PATH}")
    print(f"Saved scaler stats to {SCALER_STATS_PATH}")


if __name__ == "__main__":
    main()
