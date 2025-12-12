#include <MANTruckDataset/MANTruckDataset.hpp>
#include <MANTruckDataset/data_utils.hpp>

#include <pcl/visualization/pcl_visualizer.h>

#include <thread>
#include <chrono>
#include <filesystem>

namespace fs = std::filesystem;
namespace man_ds = man::dataset;

int main(int argc, char** argv){
  if (argc < 2){
    std::cout << "Usage: './example <dataset_path>'";
    return -1;
  }
  const fs::path datasets_path(argv[1]);
  const std::string dataset_name("v1.0-mini");
  const std::string scene_token = "073e6bb18188424ea9981e3845df54a6"; // Example scene token
  const std::vector<std::string> sensor_tokens = {
    "1c4f2bbb64f847a193c748c1c14f0574"
  };
  man_ds::MANTruckDataset dataset(datasets_path.string(), dataset_name, scene_token, sensor_tokens);
  const auto sensor_manager = dataset.get_sensor_manager();
  const auto prime_sensor = sensor_manager[sensor_tokens[0]];
  
  std::cout << "Sensor info:\n" << prime_sensor << std::endl;
  const auto data_item = prime_sensor[0];
  std::cout << "First data item:\n"
            << "\tFilename: " << data_item.get_filename() << "\n"
            << "\tTimestamp: " << data_item.get_timestamp() << std::endl;
  
  if (prime_sensor.get_modality() == "lidar"){
    pcl::visualization::PCLVisualizer viewer("Point Cloud Viewer");
    auto pointcloud = std::make_shared<man_ds::data::PointCloudT>();
    viewer.addPointCloud<man_ds::data::PointT>(pointcloud, prime_sensor.get_channel());

    for (size_t i = 0; i < prime_sensor.size(); ++i){
      const auto data_item = prime_sensor[i];
      std::cout << "Data item " << i << ":\n"
                << "\tFilename: " << data_item.get_filename() << "\n"
                << "\tTimestamp: " << data_item.get_timestamp() << std::endl;
      pointcloud = man_ds::data::read_pointcloud(data_item.get_filename());
      std::cout << "Point cloud loaded with " << pointcloud->size() << " points." << std::endl;
      viewer.updatePointCloud<man_ds::data::PointT>(pointcloud, prime_sensor.get_channel());
      viewer.spinOnce (1000);
    }
  }
  return 0;
}