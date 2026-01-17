# Changelog for MAN Truck Scenes Reader
All notable changes to this project will be documented in this file.

# [Unreleased]

## [0.5.0]

### New Features
- Access scenes list via SceneManager.get_scenes() method.
- Access samples list via SampleManager.get_samples() method.
- Removed SampleManager.get_samples() as Token vector.

### Enhancements
- Replaced DataSequence with DataManager class
- Replaced SampleSequence with SampleManager class.

### Added
- Function annotations for SceneManager, SampleManager, DataManager.

## [0.4.0]

### New Features
- Replaced token string type by special Token structure
- Update tests, examples and pybindings

## [0.3.0]

### New Features
- Added Python bindings for MAN Truck Scenes Reader.
- Examples for using the Python bindings.
- Added reading images with openCV.

## [0.2.0]

### New Features
- Added MAN Dataset class for handling datasets.
- Included examples for using the MAN Dataset class.
- SensorManager and CalibrationManager now support filtering by sensor tokens.

### Enhancements
- Scene class attributes are now private with getter methods.
- Update API for SceneManager (not backward compatible).
- Update API for SensorManager, CalibrationManager (backward compatible).

## [0.1.0]

### Added
- Initial release of MAN Truck Scenes Reader.
- Version 0.1.0

### Changed
- None.
### Fixed
- None.
