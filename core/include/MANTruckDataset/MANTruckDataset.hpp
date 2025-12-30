#pragma once
#include "MANTruckDataset/Sensor.hpp"
#include "MANTruckDataset/Calibration.hpp"
#include "MANTruckDataset/Sample.hpp"
#include "MANTruckDataset/Scene.hpp"
#include "MANTruckDataset/DataSample.hpp"
#include "MANTruckDataset/utils.hpp"

#include <string>
#include <filesystem>

namespace fs = std::filesystem;

namespace man::dataset {

class MANTruckDataset {
public:
  MANTruckDataset(
    const std::string& datasets_folder, 
    const std::string& dataset_name, 
    const Token& scene_token,
    const std::vector<Token>& sensor_tokens = {});

  const sensors::SensorManager& get_sensor_manager() const noexcept { return sensor_manager_; }
  
private:
  const fs::path DATASETS_PATH_;
  const fs::path DATASET_PATH_;
  sensors::SensorManager sensor_manager_;
  calibration::CalibrationManager calibration_manager_;
  
  scenes::SceneManager scene_manager_;
  samples::SampleSequence sample_sequence;
  data_samples::DataSequence data_sequence_;
};

}