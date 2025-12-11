#pragma once

#include <string>

#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>

#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>

namespace man::dataset::data {

using ImageT = cv::Mat;

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

ImageT read_image(const std::string& filepath)
{
  ImageT img = cv::imread(filepath, cv::IMREAD_UNCHANGED);
  if (img.empty()) {
    throw std::runtime_error("Failed to read image: " + filepath);
  }
  return img;
}
}