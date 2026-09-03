# RĀY Scent Dataset

This directory is reserved for real BME688 sensor measurements collected for the RĀY olfactory classification pipeline.

## Purpose

The scent library contains structured scent reference metadata.

This `data` directory contains actual sensor measurements used for training, testing, and validating the machine-learning models.

Reference volatile compounds listed in scent metadata are not directly identified by the BME688 sensor. They are descriptive reference information only.

## Planned Structure

```text
data/
├── baseline/
├── coffee/
├── lemon/
├── orange/
└── experiments/
Recorded Measurements

Each sensor capture should include, when available:

timestamp
scent ID
sample label
gas resistance
temperature
humidity
pressure
heater profile
capture duration
device identifier
experiment identifier
Baseline

Clean air is used as the initial baseline.

Scent ID:

ray-scent-001

A baseline capture should be recorded before scent measurements whenever practical.

Initial Classification Dataset

The first planned experiment focuses on:

Clean Air
Coffee
Lemon

The initial goal is to verify that RĀY can distinguish clearly different scent profiles before expanding the classification set.

Data Format

Initial sensor captures are expected to use CSV files.

Example:

timestamp,scent_id,label,gas_resistance,temperature,humidity,pressure,device_id
Experiments

Experimental datasets should be stored separately from validated datasets.

Each experiment should document:

environmental conditions
sample source
number of repetitions
sensor warm-up period
capture duration
sampling interval
hardware and firmware version
Status

No validated production dataset is included yet.

The current milestone is collecting reproducible BME688 measurements for the first RĀY scent classification experiment.