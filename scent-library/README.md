# RĀY Scent Library

The RĀY Scent Library is the structured olfactory knowledge base used by the RĀY digital olfaction platform.

It separates human-readable scent knowledge from raw sensor measurements and machine-learning datasets.

## Structure

```text
scent-library/
├── scents/       # Individual scent definitions
├── taxonomy/     # Families and descriptors
├── schema/       # JSON schema for scent entries
└── data/         # Sensor datasets and capture documentation
Current Scent Set

The current reference library includes:

Clean Air
Coffee
Lemon
Orange
Rose
Lavender
Peppermint
Vanilla
Cinnamon
Pine
Wet Earth
Scent Representation

Each scent entry may contain:

identity and category
scent families
olfactory descriptors
dominant notes
reference volatile compounds
BME688 sensor information
dataset references
model status
Sensor Model

Reference chemical information and sensor measurements are intentionally kept separate.

The BME688 does not directly identify individual volatile compounds. RĀY instead records changes in sensor response and uses machine-learning models to build olfactory fingerprints.

Validation

The scent library is designed around a shared JSON schema and controlled taxonomy.

Each scent must use:

a unique RĀY scent ID
valid scent families
valid descriptors
a supported sensor profile
a defined lifecycle status
Current Version

0.2.0

The next milestone is collecting real BME688 measurements and building the first scent classification dataset.

```markdown
# RĀY Sensor Dataset

This directory is reserved for measurements captured from RĀY sensor hardware.

Raw sensor measurements are intentionally separated from the reference scent definitions stored in:

```text
../scents/
Planned Dataset Structure
data/
├── baseline/
├── coffee/
├── lemon/
├── orange/
└── experiments/
Planned Measurements

Each sensor recording may include:

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

Clean-air recordings will be used as the primary baseline for comparing scent responses.

Initial Experiment

The first planned classification experiment is:

Clean Air vs Coffee vs Lemon

Future experiments will expand the dataset to additional scent families.

Important

Reference compounds listed in the scent library are descriptive chemical references.

They must not be interpreted as compounds directly detected or identified by the BME688 sensor.