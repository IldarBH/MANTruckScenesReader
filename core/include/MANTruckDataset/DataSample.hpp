#pragma once
#include "MANTruckDataset/utils.hpp"

#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <unordered_set>
#include <unordered_map>

namespace man::dataset::data_samples {
  
class DataSample {
public:
  using SPtr = std::shared_ptr<DataSample>;
  using WPtr = std::weak_ptr<DataSample>;

  DataSample(const Token& token, 
             const Token& sample_token,
             const Token& ego_pose_token,
             const Token& calibrated_sensor_token,
             const std::string& fileformat,
             const std::string& filename,
             const uint64_t timestamp,
             const Token& prev_token = Token(),
             const Token& next_token = Token());

  const auto& get_token() const noexcept { return TOKEN_; }
  const auto& get_sample_token() const noexcept { return SAMPLE_TOKEN_; }
  const auto& get_filename() const noexcept { return FILENAME_; }
  const auto& get_ego_pose_token() const noexcept { return EGO_POSE_TOKEN_; }
  const auto& get_calibrated_sensor_token() const noexcept { return CALIBRATED_SENSOR_TOKEN_; }
  const auto& get_timestamp() const noexcept { return TIMESTAMP_; }
  const std::string& get_fileformat() const noexcept { return FILEFORMAT_; }

  friend std::ostream& operator<<(std::ostream& os, const DataSample& s);

public:
  WPtr prev_sample;
  WPtr next_sample;

private:
  const Token TOKEN_;
  const Token PREV_TOKEN_;
  const Token NEXT_TOKEN_;
  const Token SAMPLE_TOKEN_;
  const Token EGO_POSE_TOKEN_;
  const Token CALIBRATED_SENSOR_TOKEN_;
  const std::string FILEFORMAT_;
  const std::string FILENAME_;
  const uint64_t TIMESTAMP_;
};

std::ostream& operator<<(std::ostream& os, const DataSample& sample);

class DataManager {
public:
  DataManager() = default;

  /**
   * @brief Read data samples from a JSON file, filtering by sample tokens.
   * Clear already loaded samples before reading.
   * @param filename Path to the JSON file.
   * @param sample_token Vector of sample tokens to filter the data samples.
   * @return True if all samples are loaded, false otherwise.
   */
  bool read_samples(const std::string& filename, const std::vector<Token>& sample_tokens);

  /**
   * @brief Add a data sample to the manager.
   * @param token Unique identifier for the data sample.
   * @param sample_token Token of the sample associated with this data sample.
   * @param ego_pose_token Token of the ego pose associated with this data sample.
   * @param calibrated_sensor_token Token of the calibrated sensor associated with this data sample.
   * @param fileformat File format of the data sample (e.g., "pcd", "png").
   * @param filename Path to the data sample file.
   * @param timestamp Timestamp of the data sample.
   * @param prev_token Token of the previous data sample (optional).
   * @param next_token Token of the next data sample (optional).
   */
  void add_sample(
    const Token& token, 
    const Token& sample_token,
    const Token& ego_pose_token,
    const Token& calibrated_sensor_token,
    const std::string& fileformat,
    const std::string& filename,
    const uint64_t timestamp,
    const Token& prev_token = Token(),
    const Token& next_token = Token());

  /**
   * @brief Check if all requested samples have been loaded.
   * @return True if all samples are loaded, false otherwise.
   */
  bool is_complete() const noexcept { return waiting_list_.empty(); }
  
  auto begin() noexcept { return samples_vec_.begin(); }
  auto end() noexcept { return samples_vec_.end(); }
  auto cbegin() const noexcept { return samples_vec_.cbegin(); }
  auto cend() const noexcept { return samples_vec_.cend(); }
  size_t size() const noexcept { return samples_vec_.size(); }

private:
  void parse_json_(const nlohmann::json& data, const std::unordered_set<Token>& sample_tokens);

private:
  std::unordered_set<Token> waiting_list_;
  std::vector<DataSample::SPtr> samples_vec_;
  std::unordered_map<Token, DataSample::WPtr> samples_map_;
};

}
