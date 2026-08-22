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
  /**
   * @brief Construct a new MANTruckDataset object.
   * @param dataset_folder Path to the dataset folder
   * @param metadata_folder Path to the metadata folder
   */
  MANTruckDataset(
    const std::string& dataset_folder, 
    const std::string& metadata_folder);

  auto& get_scene_manager() const noexcept { return scene_manager_; }
  auto& get_sensor_manager() const noexcept { return sensor_manager_; }
  auto& get_calibration_manager() const noexcept { return calibration_manager_; }
  auto& get_sample_manager() const noexcept { return sample_manager_; }
  auto& get_data_manager() const noexcept { return data_manager_; }
  
private:
  const fs::path DATASET_PATH_;
  const fs::path METADATA_PATH_;
  scenes::SceneManager scene_manager_;
  sensors::SensorManager sensor_manager_;
  calibration::CalibrationManager calibration_manager_;
  samples::SampleManager sample_manager_;
  data_samples::DataManager data_manager_;
};

}