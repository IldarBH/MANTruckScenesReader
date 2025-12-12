#include "utils.hpp"
#include <MANTruckDataset/Scene.hpp>
#include <MANTruckDataset/Sample.hpp>
#include <MANTruckDataset/DataSample.hpp>
#include <MANTruckDataset/Sensor.hpp>
#include <MANTruckDataset/Calibration.hpp>

#include <string>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;
namespace man_ds = man::dataset;

int main(int argc, char** argv){
  if (argc < 2){
    std::cout << "Usage: './example <dataset_path>'";
    return -1;
  }
  const fs::path dataset_path(argv[1]);
  
  const std::string sensors_file(dataset_path / "v1.0-mini" / "sensor.json");
  man_ds::sensors::SensorManager sensor_manager;
  sensor_manager.read_sensors(sensors_file);

  const std::string calibrations_file(dataset_path / "v1.0-mini" / "calibrated_sensor.json");
  man_ds::calibration::CalibrationManager calibration_manager;
  calibration_manager.read_calibrations(calibrations_file);

  const std::string scene_file(dataset_path / "v1.0-mini" / "scene.json");
  man_ds::scenes::SceneManager scene_manager;
  scene_manager.read_scenes(scene_file);
  const auto& scene = scene_manager[0];
  std::cout << scene << std::endl;

  const std::string sample_file(dataset_path / "v1.0-mini" / "sample.json");
  man_ds::samples::SampleSequence sample_sequence;
  sample_sequence.read_samples(sample_file, scene.get_token());
  std::cout << "Number of samples: " << sample_sequence.size() << std::endl;

  const std::string data_sample_file(dataset_path / "v1.0-mini" / "sample_data.json");
  man_ds::data_samples::DataSequence data_sequence;
  data_sequence.read_samples(data_sample_file, sample_sequence.get_tokens());
  if (!data_sequence.is_complete()){
    std::cerr << "Warning: Data sequence is incomplete." << std::endl;
  }
  std::cout << "Number of data samples: " << data_sequence.size() << std::endl;

  for (const auto& data_sample : data_sequence){
    const auto& calibrated_sensor_token = data_sample->get_calibrated_sensor_token();
    const auto& calibrated_sensor = calibration_manager[calibrated_sensor_token];
    const auto& sensor_token = calibrated_sensor.get_sensor_token();
    auto& sensor = sensor_manager[sensor_token];
    sensor.add_file(data_sample->get_filename(), data_sample->get_timestamp());
  }
  const auto& sensor = select_sensor(sensor_manager);
  std::cout << sensor << std::endl;
  return 0;
}