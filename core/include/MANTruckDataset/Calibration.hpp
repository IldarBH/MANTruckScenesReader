#pragma once
#include "MANTruckDataset/utils.hpp"
#include <Eigen/Dense>
#include <string>
#include <sstream>
#include <iostream>
#include <string_view>
#include <vector>
#include <unordered_map>

namespace man::dataset::calibration {

namespace {
constexpr std::string_view TOKEN_KEY = "token";
constexpr std::string_view SENSOR_TOKEN_KEY = "sensor_token";
}

class Calibration {
public:
  Calibration() = delete;

  Calibration(
    const std::string& token,
    const std::string& sensor_token,
    const std::vector<double>& translation,
    const std::vector<double>& rotation)
  : TOKEN_(token)
  , SENSOR_TOKEN_(sensor_token)
  , TRANSLATION_(Eigen::Vector3d(translation.data()))
  , ROTATION_(Eigen::Quaterniond(rotation.data()))
  {}

  const std::string& get_token() const noexcept { return TOKEN_; }
  const std::string& get_sensor_token() const noexcept { return SENSOR_TOKEN_; }
  const Eigen::Vector3d& get_translation() const noexcept {return TRANSLATION_; }
  const Eigen::Quaterniond& get_rotation() const noexcept { return ROTATION_; }

  friend std::ostream& operator<<(std::ostream& os, const Calibration& calib);
private:
  const std::string TOKEN_;
  const std::string SENSOR_TOKEN_;
  const Eigen::Vector3d TRANSLATION_;
  const Eigen::Quaterniond ROTATION_;
};

std::ostream& operator<<(std::ostream& os, const Calibration& calib)
{
  os << "Calibration:\n"
     << "\tToken: " << calib.get_token() << "\n"
     << "\tSensor Token: " << calib.get_sensor_token() << "\n"
     << "\tTranslation: " << calib.get_translation().transpose() << "\n"
     << "\tRotation (x,y,z,w): " << calib.get_rotation().coeffs().transpose();
  return os;
}

class CalibrationManager {
public:
  CalibrationManager() = default;

  void read_calibrations(const std::string& filename)
  {
    const auto json_file = read_json_file(filename);
    for (const auto& item : json_file) {
      const std::string token(item.at(TOKEN_KEY).get<std::string>());
      const std::string sensor_token(item.at(SENSOR_TOKEN_KEY).get<std::string>());
      const std::vector<double> translation = item["translation"].get<std::vector<double>>();
      const std::vector<double> rotation = item["rotation"].get<std::vector<double>>();
      // const std::vector<std::vector<double>> camera_intrinsic = item["camera_intrinsic"].get<std::vector<std::vector<double>>>();
      add_calibration(token, sensor_token, translation, rotation);
    }
  }

  void add_calibration(const std::string& token, const std::string& sensor_token, const std::vector<double>& translation, const std::vector<double>& rotation)
  {
    const auto iter = calibrations_.emplace(
      std::make_pair(token, Calibration(token, sensor_token, translation, rotation)));
    #ifdef DEBUG_BUILD
      std::cout << iter.first->second << std::endl;
    #endif
  }

  const Calibration& operator[](const std::string& token) const
  {
    const auto iter = calibrations_.find(token);
    if (iter == calibrations_.end()) {
      throw std::runtime_error("Calibration with token " + token + " not found.");
    }
    return iter->second;
  }
private:
  std::unordered_map<std::string, Calibration> calibrations_;
};

} // namespace