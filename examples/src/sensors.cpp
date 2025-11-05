#include <MANTruckDataset/SensorsManager.hpp>

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

  man_ds::sensors::SensorManager sm;
  sm.read_sensors(sensors_file);
  return 0;
}