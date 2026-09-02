# RĀY Sensor Capture Protocol

This document defines the initial procedure for collecting BME688 scent measurements for the RĀY project.

## 1. Sensor Warm-up

Before recording a sample, allow the BME688 sensor to warm up according to the configured warm-up duration.

Default:

```text
30 seconds
2. Baseline Capture

A clean-air baseline should be captured before scent measurements.

Baseline scent ID:

ray-scent-001
3. Sample Capture

Default capture duration:

60 seconds

Default sampling interval:

1000 ms

The system records:

gas resistance
temperature
humidity
pressure
timestamp
scent ID
device ID
4. Sample Isolation

Use one scent source at a time.

Allow the sensor environment to return close to baseline before starting the next scent capture.

5. Output

Initial measurements are stored as CSV files.

Future versions may add additional metadata such as:

experiment ID
sample repetition
heater profile
environmental notes
sensor calibration information
Goal

This protocol provides a reproducible starting point for building the first RĀY olfactory classification dataset.