#pragma once
#include "MANTruckDataset/utils.hpp"

#include <string>
#include <sstream>
#include <iostream>
#include <string_view>
#include <set>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <memory>

namespace man::dataset::sensors {

class DataItem {
public:
  using SPtr = std::shared_ptr<DataItem>;
  using WPtr = std::weak_ptr<DataItem>;

  DataItem(const size_t timestamp, 
           const std::string& filename, 
           const DataItem* prev = nullptr, 
           const DataItem* next = nullptr);

  const size_t get_timestamp() const noexcept { return TIMESTAMP_; }
  const std::string& get_filename() const noexcept { return FILENAME_; }
  DataItem* get_prev_sample() const noexcept { return prev_sample_; }
  DataItem* get_next_sample() const noexcept { return next_sample_; }
  void set_prev_sample(DataItem* prev) noexcept;
  void set_next_sample(DataItem* next) noexcept;
  
  friend bool operator<(const DataItem& a, const DataItem& b);

private:
  const size_t TIMESTAMP_;
  const std::string FILENAME_;

  DataItem* prev_sample_ = nullptr;
  DataItem* next_sample_ = nullptr;
};

inline bool operator<(const DataItem& a, const DataItem& b) {return a.TIMESTAMP_ < b.TIMESTAMP_; }

inline bool operator<(const DataItem::SPtr& a, const DataItem::SPtr& b) {return *a < *b; }

enum class SensorType {
  CAMERA,
  LIDAR,
  RADAR,
  IMU,
};

class SensorBase {
public:
  using SPtr = std::shared_ptr<SensorBase>;
  using WPtr = std::weak_ptr<SensorBase>;

  SensorBase(const Token& token, 
             const std::string& channel, 
             const SensorType modality);

  SensorBase(const Token& token, 
             const std::string& channel, 
             const std::string_view modality);

  SensorBase(const std::string& token, 
             const std::string& channel, 
             const std::string_view modality);

  const auto& get_token() const noexcept { return TOKEN_; }
  const auto& get_channel() const noexcept { return CHANNEL_; }
  const auto& get_modality() const noexcept { return MODALITY_; }
  size_t size() const noexcept { return samples_vec_.size(); }
  void add_file(const std::string& filename, const size_t timestamp);
  const DataItem operator[](const size_t index) const;
  friend std::ostream& operator<<(std::ostream& os, const SensorBase& sensor);  
private:
  const Token TOKEN_;
  const std::string CHANNEL_;
  const SensorType MODALITY_;
  std::vector<DataItem::SPtr> samples_vec_;
};

std::ostream& operator<<(std::ostream& os, const SensorBase& sensor);

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
   * @brief Add a sensor to the manager.
   * @param token Token of the sensor.
   * @param channel Channel name of the sensor.
   * @param modality Modality of the sensor.
   */
  void add_sensor(const Token& token, const std::string& channel, const std::string& modality);

  /**
   * @brief Get all sensors.
   */
  const auto& get_sensors() const noexcept { return sensors_vec_; }
  
  const SensorBase& operator[](const size_t id) const { return *sensors_vec_[id]; }
  const SensorBase& operator[](const Token& token) const { return *sensors_by_token_.at(token); };
  auto begin() { return sensors_vec_.begin(); }
  auto end() { return sensors_vec_.end(); }
  auto begin() const { return sensors_vec_.begin(); }
  auto end() const { return sensors_vec_.end(); }
  auto cbegin() const { return sensors_vec_.cbegin(); }
  auto cend() const { return sensors_vec_.cend(); }

  /**
   * @brief Get the number of sensors.
   */
  size_t size() const noexcept { return sensors_vec_.size(); }

private:
  void parse_json_(const nlohmann::json& data);

private:
  std::vector<SensorBase::SPtr> sensors_vec_;
  std::unordered_map<Token, SensorBase::SPtr> sensors_by_token_;
};

}
