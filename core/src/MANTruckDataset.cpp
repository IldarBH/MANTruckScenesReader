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

std::vector<data_samples::DataSample::WPtr> MANTruckDataset::get_data(const scenes::Scene& scene, const sensors::SensorBase& sensor) const
{
  const auto& samples = sample_manager_.get_samples_by_scene(scene.get_token());
  const auto& calibrated_sensor = calibration_manager_.get_calibration_by_sensor(sensor.get_token());

  std::vector<data_samples::DataSample::WPtr> result;
  for (const auto& sample : samples) {
    const auto& data_sample = data_manager_.get_data_by_sample_token(sample.lock()->get_token());
    if (data_sample.empty()) {
      continue;
    }
    for (const auto& data : data_sample) {
      if (data.lock()->get_calibrated_sensor_token() == calibrated_sensor.get_token()) {
        result.push_back(data);
      }
    }
  }
  return result;
}

}
