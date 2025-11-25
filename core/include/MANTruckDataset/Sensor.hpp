#pragma once
#include "MANTruckDataset/utils.hpp"

#include <string>
#include <sstream>
#include <iostream>
#include <string_view>
#include <unordered_map>
#include <memory>

namespace man::dataset::sensors {
namespace{
constexpr std::string_view TOKEN_KEY = "token";
constexpr std::string_view MODALITY_KEY = "modality";
constexpr std::string_view CHANNEL_KEY = "channel";
constexpr std::string_view LIDAR_MODALITY = "lidar";
}

class SensorBase {
public:
  using SPtr = std::shared_ptr<SensorBase>;

  SensorBase(
    const std::string& token, 
    const std::string& channel, 
    const std::string_view modality)
  : TOKEN_(token)
  , CHANNEL_(channel)
  , MODALITY_(modality) {}

  friend std::ostream& operator<<(std::ostream& os, const SensorBase& sensor);

private:
  const std::string TOKEN_;
  const std::string CHANNEL_;
  const std::string MODALITY_;
};

std::ostream& operator<<(std::ostream& os, const SensorBase& sensor)
{
  os << "Sensor:"
     << "\tToken: " << sensor.TOKEN_ << "\n"
     << "\tChannel: " << sensor.CHANNEL_ << "\n"
     << "\tModality: " << sensor.MODALITY_;
  return os;
}

class LidarSensor : public SensorBase {
public:
  using Ptr = std::shared_ptr<LidarSensor>;

  LidarSensor(const std::string token, const std::string channel)
  : SensorBase(token, channel, LIDAR_MODALITY) {};
};

class SensorManager {
public:
  SensorManager() = default;

  void read_sensors(const std::string& filename)
  {
    const auto json_file = read_json_file(filename);
    for (const auto& item : json_file) {
      const std::string modality(item.at(MODALITY_KEY).get<std::string>());
      if (modality == LIDAR_MODALITY) {
        add_lidar(item.at(TOKEN_KEY).get<std::string>(), item.at(CHANNEL_KEY).get<std::string>());
      }
    }
  }
  
  void add_lidar(const std::string& token, const std::string& channel)
  {
    const auto iter = sensors_.emplace(std::make_pair(token, std::make_shared<LidarSensor>(token, channel)));
    #ifdef DEBUG_BUILD
      std::cout << *(iter.first->second) << std::endl;
    #endif
  }
private:
  std::unordered_map<std::string, SensorBase::SPtr> sensors_;
};

}
