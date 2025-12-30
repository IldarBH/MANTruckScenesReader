#pragma once
#include "MANTruckDataset/utils.hpp"

#include <Eigen/Dense>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

namespace man::dataset::calibration {

class Calibration {
public:
  Calibration() = delete;

  Calibration(
    const Token& token,
    const Token& sensor_token,
    const std::vector<double>& translation,
    const std::vector<double>& rotation);

  const auto& get_token() const noexcept { return TOKEN_; }
  const auto& get_sensor_token() const noexcept { return SENSOR_TOKEN_; }
  const Eigen::Vector3d& get_translation() const noexcept {return TRANSLATION_; }
  const Eigen::Quaterniond& get_rotation() const noexcept { return ROTATION_; }

  friend std::ostream& operator<<(std::ostream& os, const Calibration& calib);
private:
  const Token TOKEN_;
  const Token SENSOR_TOKEN_;
  const Eigen::Vector3d TRANSLATION_;
  const Eigen::Quaterniond ROTATION_;
};

std::ostream& operator<<(std::ostream& os, const Calibration& calib);

class CalibrationManager {
public:
  CalibrationManager() = default;

  /**
   * @brief Read calibrations from a JSON file.
   * @param filename Path to the JSON file.
   * @param sensor_tokens Optional list of sensor tokens to filter calibrations.
   * @details If sensor_tokens is provided, only calibrations for the specified sensors will be loaded.
   * Be aware sensor tokens are not the same as calibration tokens.
   */
  void read_calibrations(const std::string& filename, const std::vector<Token>& sensor_tokens = {});

  void add_calibration(
    const Token& token, 
    const Token& sensor_token, 
    const std::vector<double>& translation, 
    const std::vector<double>& rotation);

  bool token_exists(const Token& token) const noexcept;

  const Calibration& operator[](const Token& token) const;

private:
  void parse_json_(const nlohmann::json& data, const std::unordered_set<Token>& filter_tokens);

private:
  std::unordered_map<Token, Calibration> calibrations_;
};

} // namespace