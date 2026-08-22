#include "MANTruckDataset/MANTruckDataset.hpp"

#include <string_view>

namespace man::dataset {

namespace {
  constexpr std::string_view DEFAULT_SENSOR_FILE = "sensor.json";
  constexpr std::string_view DEFAULT_CALIBRATION_FILE = "calibrated_sensor.json";
  constexpr std::string_view DEFAULT_SCENE_FILE = "scene.json";
  constexpr std::string_view DEFAULT_SAMPLE_FILE = "sample.json";
  constexpr std::string_view DEFAULT_DATA_SAMPLE_FILE = "sample_data.json";
}

MANTruckDataset::MANTruckDataset(const std::string& dataset_folder, const std::string& metadata_folder)
  : DATASET_PATH_(dataset_folder)
  , METADATA_PATH_(DATASET_PATH_ / metadata_folder)
  {
    if (!fs::exists(METADATA_PATH_)) {
      throw std::invalid_argument("Metadata path '" + METADATA_PATH_.string() + "' doesn't exists");
    }
    // Load scenes
    const std::string scene_file(METADATA_PATH_ / DEFAULT_SCENE_FILE);
    scene_manager_.read_scenes(scene_file);
    // Load calibrations
    const std::string calibrations_file(METADATA_PATH_ / DEFAULT_CALIBRATION_FILE);
    calibration_manager_.read_calibrations(calibrations_file);
    // Load sensors
    const std::string sensor_file(METADATA_PATH_ / DEFAULT_SENSOR_FILE);
    sensor_manager_.read_sensors(sensor_file);
    // Load samples
    const std::string sample_file(METADATA_PATH_ / DEFAULT_SAMPLE_FILE);
    sample_manager_.read_samples(sample_file);
    // Load sample data
    const std::string sample_data_file(METADATA_PATH_ / DEFAULT_DATA_SAMPLE_FILE);
    if (!data_manager_.read_samples(sample_data_file)){
      throw std::runtime_error("Failed to read sample data file: " + sample_data_file);
    }
  }
}
