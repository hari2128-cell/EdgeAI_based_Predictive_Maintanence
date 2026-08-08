# Data Acquisition Flowchart

```
Start → Read Accelerometer Sample → Push to Vibration Circular Buffer →
Read I2S Audio Frame → Push to Audio Circular Buffer →
Buffer Full? (No → loop back to Read) → Hand Window to Signal Processing → End
```

Data acquisition uses fixed-size circular buffers per sensor. A processing window is only handed off once enough samples have accumulated, ensuring consistent FFT size and predictable latency.
