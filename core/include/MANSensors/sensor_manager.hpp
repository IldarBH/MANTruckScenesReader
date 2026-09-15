#pragma once
#include "MANSensors/sensor.hpp"
#include "MANTruckDataset/utils.hpp"


namespace man::dataset::sensors {

class SensorManager {
public:
  SensorManager() = default;

  /**
   * @brief Construct a SensorManager and read sensors from a JSON file.
   * @param filename Path to the JSON file.
   */
  explicit SensorManager(const std::string& filename);

  /**
   * @brief Read sensors from a JSON file.
   * @param filename Path to the JSON file.
   * @return True if the sensors were read successfully, false otherwise.
   */
  bool read_sensors(const std::string& filename);

  /**
   * @brief Get all sensors.
   */
  const auto& get_sensors() const noexcept { return sensors_vec_; }

  /**
   * @brief Get the number of sensors.
   */
  auto size() const noexcept { return sensors_vec_.size(); }
  
  /**
   * @brief Get a sensor by its ID.
   */
  const SensorBase& operator[](const size_t id) const { return *sensors_vec_[id]; }

  /**
   * @brief Get a sensor by its token.
   */
  const SensorBase& operator[](const Token& token) const { return *sensors_by_token_.at(token); };

  auto begin() { return sensors_vec_.begin(); }
  auto end() { return sensors_vec_.end(); }
  auto begin() const { return sensors_vec_.begin(); }
  auto end() const { return sensors_vec_.end(); }
  auto cbegin() const { return sensors_vec_.cbegin(); }
  auto cend() const { return sensors_vec_.cend(); }
private:
  void add_sensor_(const Token& token, const std::string& channel, const Modality& modality);
  void add_sensor_(const Token& token, const std::string& channel, const std::string& modality);
  void parse_json_(const nlohmann::json& data);

  std::vector<SensorBase::SPtr> sensors_vec_;
  std::unordered_map<Token, SensorBase::SPtr> sensors_by_token_;
};

}