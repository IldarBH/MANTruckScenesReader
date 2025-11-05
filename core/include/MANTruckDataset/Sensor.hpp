#pragma once

#include <string>
#include <sstream>
#include <string_view>
#include <vector>
#include <memory>

namespace man::dataset::sensors {

constexpr std::string_view LIDAR_MODALITY = "lidar";

class SensorBase {
public:
  using Ptr = std::shared_ptr<SensorBase>;

  SensorBase(const std::string& token, const std::string& channel, const std::string_view modality)
  : TOKEN_(token), CHANNEL_(channel), MODALITY_(modality) {}

  std::string get_description() const 
  {
    std::stringstream ss;
    ss << "Sensor token: " << TOKEN_ 
      << "\n\tChannel: " << CHANNEL_ 
      << "\n\tModality: " << MODALITY_;
    return ss.str();
  }
  
private:
  const std::string TOKEN_;
  const std::string CHANNEL_;
  const std::string MODALITY_;
};

class LidarSensor : public SensorBase {
public:
  using Ptr = std::shared_ptr<LidarSensor>;

  LidarSensor(const std::string token, const std::string channel)
  : SensorBase(token, channel, LIDAR_MODALITY) {};
};

}
