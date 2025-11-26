#pragma once
#include "MANTruckDataset/Scene.hpp"
#include "MANTruckDataset/Sensor.hpp"
#include "MANTruckDataset/Calibration.hpp"
#include "MANTruckDataset/Sample.hpp"

#include <string>
#include <filesystem>

namespace fs = std::filesystem;

namespace man::dataset {

namespace {
constexpr std::string_view DEFAULT_SENSOR_FILE = "sensor.json";
constexpr std::string_view DEFAULT_CALIBRATION_FILE = "calibrated_sensor.json";
constexpr std::string_view DEFAULT_SCENE_FILE = "scene.json";
constexpr std::string_view DEFAULT_SAMPLE_FILE = "sample.json";
}

class MANTruckDataset {
public:
  explicit MANTruckDataset(
    const std::string& dataset_folder, 
    const std::string& scene_token,
    const std::vector<std::string>& sensor_tokens = {});
  
private:
  const fs::path DATASET_PATH_;
  sensors::SensorManager sensor_manager_;
  calibration::CalibrationManager calibration_manager_;
  
  scenes::SceneManager scene_manager_;
  samples::SampleSequence sample_sequence;
};

MANTruckDataset::MANTruckDataset(
  const std::string& dataset_folder, 
  const std::string& scene_token,
  const std::vector<std::string>& sensor_tokens)
  : DATASET_PATH_(dataset_folder)
{
  if (!fs::exists(DATASET_PATH_)) {
    throw std::invalid_argument("Dataset folder '" + dataset_folder + "' doesn't exists");
  }
  const std::string sensor_file(DATASET_PATH_ / DEFAULT_SENSOR_FILE);
  sensor_manager_.read_sensors(sensor_file);

  const std::string calibrations_file(DATASET_PATH_ / DEFAULT_CALIBRATION_FILE);
  calibration_manager_.read_calibrations(calibrations_file);
}

}