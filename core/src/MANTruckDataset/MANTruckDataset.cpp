#include "MANTruckDataset/MANTruckDataset.hpp"

#include <iostream>
#include <string_view>
#include <fstream>
#include <vector>
#include <functional>
#include <nlohmann/json.hpp>

namespace {
  const std::string_view CONFIGURATIONS_FOLDER = "v1.0-mini";
  const std::string_view SENSOR_JSON = "sensor.json";
}

nlohmann::json read_json(const std::string& filepath) {
  std::ifstream file(filepath);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file: " + filepath);
  }
  nlohmann::json json;
  file >> json;
  return json;
}


MANTruckDataset::MANTruckDataset(const std::string& dataset_folder)
: DATASET_PATH_(dataset_folder)
{
  if (!fs::exists(DATASET_PATH_)){
    throw std::invalid_argument("Dataset folder '" + dataset_folder + "' doesn't exists");
  }

  const auto sensor_file = DATASET_PATH_ / CONFIGURATIONS_FOLDER / SENSOR_JSON;
  std::cout << "Sensor file: " << sensor_file << std::endl;
  const auto sensor_json = read_json(sensor_file);
}