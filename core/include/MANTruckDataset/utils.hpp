#pragma once
#include <nlohmann/json.hpp>

#include <string>
#include <fstream>

namespace man::dataset {

  nlohmann::json read_json_file(const std::string& filepath) {
  std::ifstream file(filepath);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file: " + filepath);
  }
  nlohmann::json json;
  file >> json;
  return json;
}

}

// #ifndef PCL_NO_PRECOMPILE
// #define PCL_NO_PRECOMPILE
// #endif
// #include <pcl/point_types.h>
// #include <pcl/point_cloud.h>
// struct EIGEN_ALIGN16 PointXYZIT
// {
//   PCL_ADD_POINT4D;                  // preferred way of adding a XYZ+padding
//   float intensity;
//   uint64_t timestamp;
//   PCL_MAKE_ALIGNED_OPERATOR_NEW     // make sure our new allocators are aligned
// };
// POINT_CLOUD_REGISTER_POINT_STRUCT (PointXYZIT, 
//   (float, x, x)(float, y, y)(float, z, z)(float, intensity, intensity)(float, timestamp, timestamp))
// using PointCloud = pcl::PointCloud<PointXYZIT>;