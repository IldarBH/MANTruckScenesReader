#pragma once
#include "MANSensors/sensor.hpp"
#include "MANSensors/calibration.hpp"
#include "MANTruckDataset/utils.hpp"

namespace man::dataset::sensors {

class SensorManager {
public:
  SensorManager() = default;

  /**
   * @brief Read sensors from a JSON file.
   * @param filename Path to the JSON file.
   * @return True if the sensors were read successfully, false otherwise.
   */
  bool read_sensors(const std::string& filename);
  
  /**
   * @brief Read calibrations from a JSON file.
   * @param filename Path to the JSON file.
   * @return True if the calibrations were read successfully, false otherwise.
   */
  bool read_calibrations(const std::string& filename);

  /**
   * @brief Get all calibrations.
   */
  const auto& get_calibrations() const noexcept { return calibrations_vec_; }

  /**
   * @brief Get all sensors.
   */
  const auto& get_sensors() const noexcept { return sensors_vec_; }

  /**
   * @brief Get the number of sensors.
   */
  auto size() const noexcept { return sensors_vec_.size(); }
  
private:
  void add_calibration_(const Token& token, 
                        const Token& sensor_token, 
                        const std::vector<double>& translation, 
                        const std::vector<double>& rotation, 
                        const std::vector<std::vector<double>>& camera_matrix);
  void add_sensor_(const Token& token, 
                   const std::string& channel, 
                   const Modality& modality);
  void parse_calibrations_(const nlohmann::json& data);
  void parse_sensors_(const nlohmann::json& data);

  std::vector<Calibration::SPtr> calibrations_vec_;
  std::unordered_map<Token, Calibration::SPtr> calibrations_by_token_;

  std::vector<SensorBase::SPtr> sensors_vec_;
  std::unordered_map<Token, SensorBase::SPtr> sensors_by_token_;
};

}