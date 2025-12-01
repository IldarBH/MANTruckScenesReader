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
namespace{
constexpr std::string_view TOKEN_KEY = "token";
constexpr std::string_view MODALITY_KEY = "modality";
constexpr std::string_view CHANNEL_KEY = "channel";
constexpr std::string_view LIDAR_MODALITY = "lidar";
}

class DataItem {
public:
  using SPtr = std::shared_ptr<DataItem>;
  using WPtr = std::weak_ptr<DataItem>;

  DataItem(const size_t timestamp, const std::string& filename, 
    const DataItem* prev = nullptr, const DataItem* next = nullptr)
  : TIMESTAMP_(timestamp)
  , FILENAME_(filename)
  {}

  const size_t get_timestamp() const noexcept { return TIMESTAMP_; }
  const std::string& get_filename() const noexcept { return FILENAME_; }
  DataItem* get_prev_sample() const noexcept { return prev_sample_; }
  DataItem* get_next_sample() const noexcept { return next_sample_; }

  void set_prev_sample(DataItem* prev) noexcept 
  { 
    prev_sample_ = prev;
    if (prev && (prev->get_next_sample() != this))
      prev->set_next_sample(this);
  }

  void set_next_sample(DataItem* next) noexcept 
  { 
    next_sample_ = next; 
    if (next && (next->get_prev_sample() != this))
      next->set_prev_sample(this);
  }
  
  friend bool operator<(const DataItem& a, const DataItem& b);

private:
  const size_t TIMESTAMP_;
  const std::string FILENAME_;

  DataItem* prev_sample_ = nullptr;
  DataItem* next_sample_ = nullptr;
};

inline bool operator<(const DataItem& a, const DataItem& b) {
  return a.TIMESTAMP_ < b.TIMESTAMP_;
}

inline bool operator<(const DataItem::SPtr& a, const DataItem::SPtr& b) {
  return *a < *b;
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

  size_t size() const noexcept { return samples_vec_.size(); }
  
  void add_file(const std::string& filename, const size_t timestamp) 
  { 
    if (samples_vec_.empty()){
      samples_vec_.emplace_back(std::make_shared<DataItem>(timestamp, filename));
    } else {
      const auto& last_sample = samples_vec_.back();
      auto new_sample = std::make_shared<DataItem>(timestamp, filename, last_sample.get());
      samples_vec_.emplace_back(std::move(new_sample));
    }
    
  }

  const DataItem operator[](const size_t index) const 
  { 
    if (index >= samples_vec_.size()) {
      throw std::out_of_range("Index " + std::to_string(index) + " out of range.");
    }
    return *samples_vec_[index]; 
  }
private:
  const std::string TOKEN_;
  const std::string CHANNEL_;
  const std::string MODALITY_;
  std::vector<DataItem::SPtr> samples_vec_;
};

std::ostream& operator<<(std::ostream& os, const SensorBase& sensor)
{
  os << "Sensor:\n"
     << "\tToken: " << sensor.TOKEN_ << "\n"
     << "\tChannel: " << sensor.CHANNEL_ << "\n"
     << "\tModality: " << sensor.MODALITY_ << "\n"
     << "\tFiles cound: " << sensor.samples_vec_.size();
  return os;
}

class SensorManager {
public:
  SensorManager() = default;

  /**
   * @brief Read sensors from a JSON file.
   * @param filename Path to the JSON file.
   * @param filter_tokens Optional list of sensor tokens to filter sensors.
   * @details If filter_tokens is provided, only sensors with the specified tokens will be loaded.
   */
  void read_sensors(const std::string& filename, const std::vector<std::string>& filter_tokens = {})
  {
    const std::unordered_set<std::string> filter_set(filter_tokens.begin(), filter_tokens.end());
    const auto json_file = read_json_file(filename);
    this->parse_json_(json_file, filter_set);
  }

  void add_sensor(const std::string& token, const std::string& channel, const std::string& modality)
  {
    const auto iter = sensors_.emplace(std::make_pair(token, SensorBase(token, channel, modality)));
    #ifdef DEBUG_BUILD
      std::cout << iter.first->second << std::endl;
    #endif
  }

  SensorBase& operator[](const std::string& token)
  {
    const auto iter = sensors_.find(token);
    if (iter == sensors_.end()) {
      throw std::runtime_error("Sensor with token " + token + " not found.");
    }
    return iter->second;
  }

  const SensorBase& operator[](const std::string& token) const
  {
    const auto iter = sensors_.find(token);
    if (iter == sensors_.end()) {
      throw std::runtime_error("Sensor with token " + token + " not found.");
    }
    return iter->second;
  }

  size_t size() const noexcept { return sensors_.size(); }

  auto begin() { return sensors_.begin(); }
  auto end() { return sensors_.end(); }
  auto begin() const { return sensors_.cbegin(); }
  auto end() const { return sensors_.cend(); }

private:
  void parse_json_(const nlohmann::json& data, const std::unordered_set<std::string>& filter_tokens)
  {
    for (const auto& item : data) {
      const std::string token(item.at(TOKEN_KEY).get<std::string>());
      if (!filter_tokens.empty() && (filter_tokens.find(token) == filter_tokens.end())) {
        continue;
      }
      add_sensor(
        item.at(TOKEN_KEY).get<std::string>(), 
        item.at(CHANNEL_KEY).get<std::string>(), 
        item.at(MODALITY_KEY).get<std::string>());
    }
  }

private:
  std::unordered_map<std::string, SensorBase> sensors_;
};

}
