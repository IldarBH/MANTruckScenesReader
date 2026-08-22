#pragma once
#include "MANTruckDataset/utils.hpp"

#include <Eigen/Dense>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

namespace man::dataset::calibration {

class Calibration {
public:
  using SPtr = std::shared_ptr<Calibration>;
  using WPtr = std::weak_ptr<Calibration>;

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
   * @details If sensor_tokens is provided, only calibrations for the specified sensors will be loaded.
   * Be aware sensor tokens are not the same as calibration tokens.
   */
  void read_calibrations(const std::string& filename);

  void add_calibration(
    const Token& token, 
    const Token& sensor_token, 
    const std::vector<double>& translation, 
    const std::vector<double>& rotation);

  const Calibration& get_calibration(const Token& token) const;
  const Calibration& get_calibration_by_sensor(const Token& token) const;
private:
  void parse_json_(const nlohmann::json& data);

private:
  std::vector<Calibration::SPtr> calibrations_;
  std::unordered_map<Token, Calibration::WPtr> token2calibration_;
  std::unordered_map<Token, Calibration::WPtr> sensor_token2calibration_;
};

} // namespace