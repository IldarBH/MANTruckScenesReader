#include "MANSensors/modality.hpp"

namespace man::dataset::sensors {

namespace {
constexpr std::string_view LIDAR_MODALITY = "lidar";
constexpr std::string_view CAMERA_MODALITY = "camera";
constexpr std::string_view RADAR_MODALITY = "radar";
constexpr std::string_view IMU_MODALITY = "imu";
}

Modality string_to_modality(const std::string_view modality) 
{
  if (modality == LIDAR_MODALITY) {
    return Modality::LIDAR;
  } else if (modality == CAMERA_MODALITY) {
    return Modality::CAMERA;
  } else if (modality == RADAR_MODALITY) {
    return Modality::RADAR;
  } else if (modality == IMU_MODALITY) {
    return Modality::IMU;
  } else {
    throw std::invalid_argument("Unknown modality modality: " + std::string(modality));
  }
}

std::string modality_to_string(const Modality modality) 
{
  switch (modality) {
    case Modality::LIDAR:
      return std::string(LIDAR_MODALITY);
    case Modality::CAMERA:
      return std::string(CAMERA_MODALITY);
    case Modality::RADAR:
      return std::string(RADAR_MODALITY);
    case Modality::IMU:
      return std::string(IMU_MODALITY);
    default:
      throw std::invalid_argument("Unknown modality type");
  }
}

std::ostream& operator<<(std::ostream& os, const Modality type) 
{
  return os << modality_to_string(type);
}

}