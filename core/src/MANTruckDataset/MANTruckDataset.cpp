#include "MANTruckDataset/MANTruckDataset.hpp"

#include <string_view>
#include <unordered_map>

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
  // Load sensors and calibrations
  const std::string sensor_file(METADATA_PATH_ / DEFAULT_SENSOR_FILE);
  const std::string calibrations_file(METADATA_PATH_ / DEFAULT_CALIBRATION_FILE);
  sensor_manager_.read_sensors(sensor_file);
  sensor_manager_.read_calibrations(calibrations_file);
  // Load samples and data items
  const std::string sample_file(METADATA_PATH_ / DEFAULT_SAMPLE_FILE);
  const std::string data_item_file(METADATA_PATH_ / DEFAULT_DATA_SAMPLE_FILE);
  sample_manager_.read_samples(sample_file);
  sample_manager_.read_samples_data(data_item_file);
}

scenes::Scene::SPtr select_scene(const MANTruckDataset& dataset, std::ostream& os, std::istream& is)
{
  const auto& scenes = dataset.get_scene_manager().get_scenes();
  std::unordered_map<size_t, scenes::Scene::WPtr> scene_map;
  os << "Select scene to load:" << std::endl;
  for (const auto& scene : scenes) {
    const auto [iter, res] = scene_map.emplace(std::make_pair(scene_map.size(), scene));
    os << iter->first << ". " << *(iter->second.lock()) << std::endl;
  }
  os << "Enter selection (1-" << scenes.size() << "): ";

  size_t selection = 0;
  while (selection < 1 || selection > scenes.size()){
    is >> selection;
    if (selection < 1 || selection > scenes.size()){
      std::cerr << "Invalid selection! Try again." << std::endl;
    }
  }
  return scene_map.at(selection - 1).lock();
}

}
