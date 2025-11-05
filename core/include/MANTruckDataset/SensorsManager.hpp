#pragma once
#include "MANTruckDataset/Sensor.hpp"
#include "MANTruckDataset/utils.hpp"

#include <string>
#include <string_view>
#include <iostream>
#include <fstream>
#include <unordered_map>

namespace {
  const std::string_view MODALITY_KEY = "modality";
  const std::string_view TOKEN_KEY = "token";
  const std::string_view CHANNEL_KEY = "channel";
}

namespace man::dataset::sensors {

class SensorManager {
public:
  SensorManager() = default;

  void read_sensors(const std::string& filename)
  {
    const auto json_file = read_json_file(filename);
    for (const auto& item : json_file) {
      const std::string modality(item[std::string(MODALITY_KEY)]);
      if (modality == std::string(LIDAR_MODALITY)){
        this->add_lidar(item[TOKEN_KEY].get<std::string>(), item[CHANNEL_KEY].get<std::string>());
      }
    }
  }
  
  void add_lidar(const std::string& token, const std::string& channel)
  {
    const auto iter = sensors_.emplace(std::make_pair(token, std::make_shared<LidarSensor>(token, channel)));
    #ifdef DEBUG_BUILD
      std::cout << iter.first->second->get_description() << std::endl;
    #endif
  }
private:
  std::unordered_map<std::string, SensorBase::Ptr> sensors_;
};

}