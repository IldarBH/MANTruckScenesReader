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

MANTruckDataset::MANTruckDataset(
  const std::string& datasets_folder, 
  const std::string& dataset_name, 
  const Token& scene_token, 
  const std::vector<Token>& sensor_tokens)
  : DATASETS_PATH_(datasets_folder)
  , DATASET_PATH_(DATASETS_PATH_ / dataset_name)
  {
    if (!fs::exists(DATASET_PATH_)) {
      throw std::invalid_argument("Dataset folder '" + DATASET_PATH_.string() + "' doesn't exists");
    }
    const std::string sensor_file(DATASET_PATH_ / DEFAULT_SENSOR_FILE);
    sensor_manager_.read_sensors(sensor_file, sensor_tokens);

    const std::string calibrations_file(DATASET_PATH_ / DEFAULT_CALIBRATION_FILE);
    calibration_manager_.read_calibrations(calibrations_file, sensor_tokens);

    const std::string scene_file(DATASET_PATH_ / DEFAULT_SCENE_FILE);
    scene_manager_.read_scenes(scene_file);
    const auto& scene = scene_manager_[scene_token];

    const std::string sample_file(DATASET_PATH_ / DEFAULT_SAMPLE_FILE);
    sample_sequence.read_samples(sample_file, scene.get_token());

    const std::string data_sample_file(DATASET_PATH_ / DEFAULT_DATA_SAMPLE_FILE);
    data_sequence_.read_samples(data_sample_file, sample_sequence.get_tokens());
    if (!data_sequence_.is_complete()){
      throw std::runtime_error("Data samples sequence is not incomplete.");
    }

    for (const auto data_sample : data_sequence_){
      const auto& calibrated_sensor_token = data_sample->get_calibrated_sensor_token();
      if (calibration_manager_.token_exists(calibrated_sensor_token)){
        const auto& calibrated_sensor = calibration_manager_[calibrated_sensor_token];
        const auto& sensor_token = calibrated_sensor.get_sensor_token();  
        auto& sensor = sensor_manager_[Token(sensor_token)];
        const auto full_filename = DATASETS_PATH_ / data_sample->get_filename();
        sensor.add_file(full_filename.string(), data_sample->get_timestamp());
      }
    }
  }

}
