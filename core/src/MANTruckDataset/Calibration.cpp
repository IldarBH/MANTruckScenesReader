#include <MANTruckDataset/Calibration.hpp>

#include <string_view>
#include <iostream>
#include <sstream>

namespace man::dataset::calibration {

namespace {
    constexpr std::string_view TOKEN_KEY = "token";
    constexpr std::string_view SENSOR_TOKEN_KEY = "sensor_token";
}

Calibration::Calibration(const Token& token, const Token& sensor_token, 
  const std::vector<double>& translation, const std::vector<double>& rotation)
: TOKEN_(token)
, SENSOR_TOKEN_(sensor_token)
, TRANSLATION_(Eigen::Vector3d(translation.data()))
, ROTATION_(Eigen::Quaterniond(rotation.data()))
{}

std::ostream& operator<<(std::ostream& os, const Calibration& calib)
{
  os << "Calibration:\n"
     << "\tToken: " << calib.get_token() << "\n"
     << "\tSensor Token: " << calib.get_sensor_token() << "\n"
     << "\tTranslation: " << calib.get_translation().transpose() << "\n"
     << "\tRotation (x,y,z,w): " << calib.get_rotation().coeffs().transpose();
  return os;
}

void CalibrationManager::read_calibrations(const std::string& filename)
{
  calibrations_.clear();
  const auto json_file = read_json_file(filename);
  this->parse_json_(json_file);
}

void CalibrationManager::parse_json_(const nlohmann::json& data)
{
  for (const auto& item : data) {
    const Token calib_token(item.at(TOKEN_KEY).get<std::string>());
    const Token sensor_token(item.at(SENSOR_TOKEN_KEY).get<std::string>());
    add_calibration(
      calib_token, 
      sensor_token, 
      item["translation"].get<std::vector<double>>(), 
      item["rotation"].get<std::vector<double>>()
    );
  }
}

void CalibrationManager::add_calibration(const Token& token, const Token& sensor_token, 
  const std::vector<double>& translation, const std::vector<double>& rotation)
{
  calibrations_.emplace_back(std::make_shared<Calibration>(token, sensor_token, translation, rotation));
  calibration_by_token_.emplace(token, calibrations_.back());
  calibration_by_sensor_token_.emplace(sensor_token, calibrations_.back());
}

const Calibration& CalibrationManager::get_calibration(const Token& token) const
{
  const auto it = calibration_by_token_.find(token);
  if (it == calibration_by_token_.end()) {
    throw std::runtime_error("Calibration not found for token: " + token.value);
  }
  return *(it->second.lock());
}

const Calibration& CalibrationManager::get_calibration_by_sensor(const Token& token) const
{
  const auto it = calibration_by_sensor_token_.find(token);
  if (it == calibration_by_sensor_token_.end()) {
    throw std::runtime_error("Calibration not found for sensor token: " + token.value);
  }
  return *(it->second.lock());
}

}