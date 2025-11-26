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
  using WPtr = std::weak_ptr<SensorBase>;

  SensorBase(
    const std::string& token, 
    const std::string& channel, 
    const std::string_view modality)
  : TOKEN_(token)
  , CHANNEL_(channel)
  , MODALITY_(modality) {}

  friend std::ostream& operator<<(std::ostream& os, const SensorBase& sensor);

  const std::string& get_token() const noexcept { return TOKEN_; }
  const std::string& get_channel() const noexcept { return CHANNEL_; }
  const std::string& get_modality() const noexcept { return MODALITY_; }
public:
  std::vector<std::string> files;

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
  if (!sensor.files.empty()){
    os << "\n\tFiles: ";
    for (const auto& file : sensor.files){
      os << file << ", ";
    }
    os.seekp(-2, os.cur); // Remove last comma
  }
  return os;
}

class LidarSensor : public SensorBase {
public:
  using SPtr = std::shared_ptr<LidarSensor>;

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
      } else {
        add_sensor(item.at(TOKEN_KEY).get<std::string>(), item.at(CHANNEL_KEY).get<std::string>(), modality);
      }
    }
  }
  
  void add_lidar(const std::string& token, const std::string& channel)
  {
    const auto iter = lidars_.emplace(std::make_pair(token, std::make_shared<LidarSensor>(token, channel)));
    sensors_.emplace(std::make_pair(token, iter.first->second));
    #ifdef DEBUG_BUILD
      std::cout << *(iter.first->second) << std::endl;
    #endif
  }

  void add_sensor(const std::string& token, const std::string& channel, const std::string& modality)
  {
    const auto iter = others_.emplace(std::make_pair(token, std::make_shared<SensorBase>(token, channel, modality)));
    sensors_.emplace(std::make_pair(token, iter.first->second));
    #ifdef DEBUG_BUILD
      std::cout << *(iter.first->second) << std::endl;
    #endif
  }

  SensorBase& operator[](const std::string& token) const
  {
    const auto iter = sensors_.find(token);
    if (iter == sensors_.end()) {
      throw std::runtime_error("Sensor with token " + token + " not found.");
    }
    return *iter->second.lock();
  }

  size_t size() const noexcept { return sensors_.size(); }

  auto begin() { return sensors_.begin(); }
  auto end() { return sensors_.end(); }
  auto begin() const { return sensors_.cbegin(); }
  auto end() const { return sensors_.cend(); }

private:
  std::unordered_map<std::string, SensorBase::SPtr> others_;
  std::unordered_map<std::string, LidarSensor::SPtr> lidars_;
  std::unordered_map<std::string, SensorBase::WPtr> sensors_;
};

}
