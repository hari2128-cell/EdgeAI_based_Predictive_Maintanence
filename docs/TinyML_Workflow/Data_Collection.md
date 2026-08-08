# TinyML Workflow — Data Collection
Vibration and acoustic samples are recorded per machine state (Healthy / Warning / Fault) using the ESP32 in a "data logging" firmware mode (see `tinyml/Data_Collection/`), which streams raw/pre-windowed sensor data over serial to a host machine for storage as CSV files under `datasets/Raw/` and `tinyml/Dataset/<Class>/`.

**Captured per sample:** accelerometer axis readings, audio amplitude frames, timestamp, and a manually-assigned ground-truth label.
**Recommended practice:** collect multiple sessions per class, across different times/conditions, to reduce overfitting to a single recording session.
