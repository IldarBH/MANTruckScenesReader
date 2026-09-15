#include "MANSensors/sensor_manager.hpp"
#include "MANSensors/sensor.hpp"
#include "MANTruckDataset/utils.hpp"

#include <nlohmann/json.hpp>

#include <string>
#include <string_view>
#include <iostream>

namespace man::dataset::sensors {

namespace {
constexpr std::string_view TOKEN_KEY = "token";
constexpr std::string_view MODALITY_KEY = "modality";
constexpr std::string_view CHANNEL_KEY = "channel";
}

bool SensorManager::read_sensors(const std::string& filename)
{
  try {
    const auto json_file = read_json_file(filename);
    this->parse_json_(json_file);
  } catch (const std::exception& e) {
    std::cerr << "Error reading JSON file: " << e.what() << std::endl;
    return false;
  }
  return true;
}

void SensorManager::parse_json_(const nlohmann::json& data)
{
  for (const auto& item : data) {
    const Token token(item.at(TOKEN_KEY).get<std::string>());
    const std::string channel(item.at(CHANNEL_KEY).get<std::string>());
    const std::string modality(item.at(MODALITY_KEY).get<std::string>());
    this->add_sensor_(token, channel, modality);
  }
}

void SensorManager::add_sensor_(const Token& token, const std::string& channel, const Modality& modality)
{
  sensors_vec_.emplace_back(std::make_shared<SensorBase>(token, channel, modality));    // Index based access
  sensors_by_token_[token] = sensors_vec_.back();                                       // Token based access
}

void SensorManager::add_sensor_(const Token& token, const std::string& channel, const std::string& modality)
{
  this->add_sensor_(token, channel, string_to_modality(modality));
}

}