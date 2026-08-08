# Dataset — Fault

Raw and/or windowed sensor recordings labeled **Fault**.

## Expected File Format
CSV files, one row per sample:
```
timestamp,accel_x,accel_y,accel_z,audio_sample,label
```

## Naming Convention
fault_session<NN>_<yyyymmdd>.csv (e.g. fault_session01_20260601.csv)

## Status
No data files present yet. Add recorded sessions here following the schema above; tinyml/Data_Collection/ provides scripts to log data from the ESP32 in this format.
