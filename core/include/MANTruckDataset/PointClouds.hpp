#pragma once

#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>

namespace man::dataset::data {
using PointT = pcl::PointXYZI;
using PointCloudT = pcl::PointCloud<PointT>;

PointCloudT::Ptr read_pointcloud(const std::string& filepath)
{
  auto cloud = std::make_shared<PointCloudT>();
  if (pcl::io::loadPCDFile<PointT>(filepath, *cloud) == -1) //* load the file
  {
    PCL_ERROR("Couldn't read file %s \n", filepath.c_str());
    throw std::runtime_error("Couldn't read point cloud file " + filepath);
  }
  return cloud;
}
}