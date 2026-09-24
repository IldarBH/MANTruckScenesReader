#pragma once
#include "MANSensors/sensor_manager.hpp"
#include "MANSamples/sample_manager.hpp"
#include "MANScenes/scene_manager.hpp"
#include "MANTruckDataset/utils.hpp"

#include <string>
#include <iostream>
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
  auto& get_sample_manager() const noexcept { return sample_manager_; }
  
private:
  const fs::path DATASET_PATH_;
  const fs::path METADATA_PATH_;
  scenes::SceneManager scene_manager_;
  sensors::SensorManager sensor_manager_;
  samples::SampleManager sample_manager_;
};

scenes::Scene::SPtr select_scene(const MANTruckDataset& dataset, std::ostream& os = std::cout, std::istream& is = std::cin);

}