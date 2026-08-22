#include "utils.hpp"
#include <MANTruckDataset/MANTruckDataset.hpp>
#include <MANTruckDataset/data_utils.hpp>

#include <pcl/visualization/pcl_visualizer.h>

#include <thread>
#include <chrono>
#include <filesystem>

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
  const auto& sensor = select_sensor(dataset.get_sensor_manager());
  


  
  // const auto prime_sensor = sensor_manager[man_ds::Token(sensor_tokens[0])];
  
  // std::cout << "Sensor info:\n" << prime_sensor << std::endl;
  // const auto data_item = prime_sensor[0];
  // std::cout << "First data item:\n"
  //           << "\tFilename: " << data_item.get_filename() << "\n"
  //           << "\tTimestamp: " << data_item.get_timestamp() << std::endl;
  
  // if (prime_sensor.get_modality() == "lidar"){
  //   pcl::visualization::PCLVisualizer viewer("Point Cloud Viewer");
  //   auto pointcloud = std::make_shared<man_ds::data::PointCloudT>();
  //   viewer.addPointCloud<man_ds::data::PointT>(pointcloud, prime_sensor.get_channel());

  //   for (size_t i = 0; i < prime_sensor.size(); ++i){
  //     const auto data_item = prime_sensor[i];
  //     std::cout << "Data item " << i << ":\n"
  //               << "\tFilename: " << data_item.get_filename() << "\n"
  //               << "\tTimestamp: " << data_item.get_timestamp() << std::endl;
  //     pointcloud = man_ds::data::read_pointcloud(data_item.get_filename());
  //     std::cout << "Point cloud loaded with " << pointcloud->size() << " points." << std::endl;
  //     viewer.updatePointCloud<man_ds::data::PointT>(pointcloud, prime_sensor.get_channel());
  //     viewer.spinOnce (1000);
  //   }
  // }
  return 0;
}