#include "MANTruckDataset/MANTruckDataset.hpp"

#include <string_view>

namespace {
  const std::string_view CONFIGURATIONS_FOLDER = "v1.0-mini";
  const std::string_view SENSOR_JSON = "sensor.json";
  const std::string_view CALIBRATION_JSON = "calibrated_sensor.json";
}

MANTruckDataset::MANTruckDataset(const std::string& dataset_folder)
: DATASET_PATH_(dataset_folder)
{
  if (!fs::exists(DATASET_PATH_)) {
    throw std::invalid_argument("Dataset folder '" + dataset_folder + "' doesn't exists");
  }
}