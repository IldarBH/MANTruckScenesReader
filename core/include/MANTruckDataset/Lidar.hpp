#pragma once
#ifndef PCL_NO_PRECOMPILE
#define PCL_NO_PRECOMPILE
#endif

#include "Sensor.hpp"

#include <pcl/point_types.h>
#include <pcl/point_cloud.h>

#include <string_view>

struct EIGEN_ALIGN16 PointXYZIT
{
  PCL_ADD_POINT4D;                  // preferred way of adding a XYZ+padding
  float intensity;
  uint64_t timestamp;
  PCL_MAKE_ALIGNED_OPERATOR_NEW     // make sure our new allocators are aligned
};

POINT_CLOUD_REGISTER_POINT_STRUCT (PointXYZIT, 
  (float, x, x)(float, y, y)(float, z, z)(float, intensity, intensity)(float, timestamp, timestamp))

using PointCloud = pcl::PointCloud<PointXYZIT>;

constexpr std::string_view LIDAR_MODALITY = "LIDAR";

class Lidar : public SensorBase<PointCloud> {
public:
  Lidar(const std::string token, const std::string channel)
  : SensorBase(token, channel, LIDAR_MODALITY)
  {

  };

  PointCloud operator[](const size_t index) const override
  {
    return PointCloud();
  };
};