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
  return 0;
}