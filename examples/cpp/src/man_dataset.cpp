#include "utils.hpp"
#include <MANTruckDataset/MANTruckDataset.hpp>
#include <MANTruckDataset/data_utils.hpp>

#include <pcl/visualization/pcl_visualizer.h>

#include <thread>
#include <chrono>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;
namespace man_ds = man::dataset;

int main(int argc, char** argv){
  if (argc < 3){
    std::cout << "Usage: " << argv[0] << " <datasets_path> <metadata_folder>" << std::endl;
    std::cout << "Example: " << argv[0] << " /path/to/datasets man_truck_dataset" << std::endl;
    return -1;
  }
  const std::string dataset_folder(argv[1]);
  const std::string metadata_folder(argv[2]);
  man_ds::MANTruckDataset dataset(dataset_folder, metadata_folder);

  // Print scenes and select one
  const auto& scene = select_scene(dataset.get_scene_manager());
  std::cout << "Selected scene:\n\t" << scene << std::endl;
  const auto& sensor = select_sensor(dataset.get_sensor_manager());
  std::cout << "Selected sensor:\n\t" << sensor << std::endl;

  const auto sensor_data = dataset.get_data(scene, sensor);
  std::cout << "Data count:\n" << sensor_data.size() << std::endl;
  return 0;
}