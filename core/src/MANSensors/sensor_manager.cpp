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

constexpr std::string_view SENSOR_TOKEN_KEY = "sensor_token";
constexpr std::string_view TRANSLATION_KEY = "translation";
constexpr std::string_view ROTATION_KEY = "rotation";
constexpr std::string_view CAMERA_INTRINSIC_KEY = "camera_intrinsic";
}

bool SensorManager::read_sensors(const std::string& filename)
{
  try {
    const auto json_file = read_json_file(filename);
    this->parse_sensors_(json_file);
  } catch (const std::exception& e) {
    std::cerr << "Error reading JSON file: " << e.what() << std::endl;
    return false;
  }
  return true;
}

bool SensorManager::read_calibrations(const std::string& filename)
{
  try {
    const auto json_file = read_json_file(filename);
    this->parse_calibrations_(json_file);
  } catch (const std::exception& e) {
    std::cerr << "Error reading JSON file: " << e.what() << std::endl;
    return false;
  }
  return true;
}

void SensorManager::parse_calibrations_(const nlohmann::json& data)
{
  for (const auto& item : data) {
    const Token calib_token(item.at(TOKEN_KEY).get<std::string>());
    const Token sensor_token(item.at(SENSOR_TOKEN_KEY).get<std::string>());
    const auto translation = item.at(TRANSLATION_KEY).get<std::vector<double>>();
    const auto rotation = item.at(ROTATION_KEY).get<std::vector<double>>();
    const auto intrinsics = item.at(CAMERA_INTRINSIC_KEY).get<std::vector<std::vector<double>>>();
    this->add_calibration_(calib_token, sensor_token, translation, rotation, intrinsics);
  }
}

void SensorManager::parse_sensors_(const nlohmann::json& data)
{
  for (const auto& item : data) {
    const Token token(item.at(TOKEN_KEY).get<std::string>());
    const std::string channel(item.at(CHANNEL_KEY).get<std::string>());
    const std::string modality(item.at(MODALITY_KEY).get<std::string>());
    this->add_sensor_(token, channel, string_to_modality(modality));
  }
}

void SensorManager::add_calibration_(const Token& token, const Token& sensor_token, 
  const std::vector<double>& translation, const std::vector<double>& rotation, const std::vector<std::vector<double>>& camera_matrix)
{
  calibrations_vec_.emplace_back(std::make_shared<Calibration>(token, sensor_token, translation, rotation, camera_matrix));    // Index based access
  calibrations_by_token_[token] = calibrations_vec_.back();                                       // Token based access
}

void SensorManager::add_sensor_(const Token& token, const std::string& channel, const Modality& modality)
{
  sensors_vec_.emplace_back(std::make_shared<SensorBase>(token, channel, modality));    // Index based access
  sensors_by_token_[token] = sensors_vec_.back();                                       // Token based access
}
}