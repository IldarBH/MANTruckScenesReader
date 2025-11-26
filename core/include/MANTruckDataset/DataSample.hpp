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

  DataSample(const std::string& token, 
             const std::string& sample_token,
             const std::string& ego_pose_token,
             const std::string& calibrated_sensor_token,
             const std::string& fileformat,
             const std::string& filename,
             uint64_t timestamp,
             const std::string& prev_token = "",
             const std::string& next_token = "")
  : TOKEN_(token), 
    SAMPLE_TOKEN_(sample_token),
    EGO_POSE_TOKEN_(ego_pose_token),
    CALIBRATED_SENSOR_TOKEN_(calibrated_sensor_token),
    TIMESTAMP_(timestamp),
    FILEFORMAT_(fileformat),
    FILENAME_(filename),
    PREV_TOKEN_(prev_token),
    NEXT_TOKEN_(next_token) {}

  const std::string& get_token() const noexcept { return TOKEN_; }
  const std::string& get_sample_token() const noexcept { return SAMPLE_TOKEN_; }
  const std::string& get_filename() const noexcept { return FILENAME_; }
  const std::string& get_ego_pose_token() const noexcept { return EGO_POSE_TOKEN_; }
  const std::string& get_calibrated_sensor_token() const noexcept { return CALIBRATED_SENSOR_TOKEN_; }
  uint64_t get_timestamp() const noexcept { return TIMESTAMP_; }
  const std::string& get_fileformat() const noexcept { return FILEFORMAT_; }

  friend std::ostream& operator<<(std::ostream& os, const DataSample& s);

public:
  WPtr prev_sample;
  WPtr next_sample;
private:
  const std::string TOKEN_;
  const std::string SAMPLE_TOKEN_;
  const std::string EGO_POSE_TOKEN_;
  const std::string CALIBRATED_SENSOR_TOKEN_;
  const std::string FILEFORMAT_;
  const uint64_t TIMESTAMP_;
  const std::string FILENAME_;
  const std::string PREV_TOKEN_;
  const std::string NEXT_TOKEN_;
};

inline std::ostream& operator<<(std::ostream& os, const DataSample& sample) {
  os << "Data sample:\n"
     << "\tToken: " << sample.TOKEN_ << "\n"
     << "\tSample token: " << sample.SAMPLE_TOKEN_ << "\n"
     << "\tCalibrated sensor token: " << sample.CALIBRATED_SENSOR_TOKEN_ << "\n"
     << "\tTimestamp: " << sample.TIMESTAMP_ << "\n"
     << "\tFilename: " << sample.FILENAME_ ;
  return os;
}

namespace {
constexpr std::string_view SAMPLE_FIELD_TOKEN = "token";
constexpr std::string_view SAMPLE_FIELD_SAMPLE_TOKEN = "sample_token";
constexpr std::string_view SAMPLE_FIELD_EGO_POSE_TOKEN = "ego_pose_token";
constexpr std::string_view SAMPLE_FIELD_CALIBRATED_SENSOR_TOKEN = "calibrated_sensor_token";
constexpr std::string_view SAMPLE_FIELD_TIMESTAMP = "timestamp";
constexpr std::string_view SAMPLE_FIELD_FILEFORMAT = "fileformat";
constexpr std::string_view SAMPLE_FIELD_FILENAME = "filename";
constexpr std::string_view SAMPLE_FIELD_PREV = "prev";
constexpr std::string_view SAMPLE_FIELD_NEXT = "next";
}

class DataSequence {
public:
  DataSequence() = default;

  /**
   * @brief Read data samples from a JSON file, filtering by sample tokens.
   * @param filename Path to the JSON file.
   * @param sample_token Vector of sample tokens to filter the data samples.
   */
  void read_samples(const std::string& filename, const std::vector<std::string>& sample_token)
  {
    const auto data = read_json_file(filename);
    const std::unordered_set<std::string> sample_tokens(sample_token.begin(), sample_token.end());
    this->parse_json_(data, sample_tokens);
  }

  /**
   * @brief Read data samples from a JSON file for a single sample token.
   * @param filename Path to the JSON file.
   * @param sample_token Sample token to filter the data samples.
   */
  void read_samples(const std::string& filename, const std::string& sample_token)
  {
    this->read_samples(filename, std::vector<std::string>{sample_token});
  }

  void add_sample(
    const std::string& token, 
    const std::string& sample_token,
    const std::string& ego_pose_token,
    const std::string& calibrated_sensor_token,
    const std::string& fileformat,
    const std::string& filename,
    uint64_t timestamp,
    const std::string& prev_token = "",
    const std::string& next_token = "")
  {
    if (samples_map_.find(token) != samples_map_.end()) {
      throw std::invalid_argument("Sample with token " + token + " already exists.");
    }
    samples_vec_.emplace_back(std::make_shared<DataSample>(token, sample_token, ego_pose_token, calibrated_sensor_token, fileformat, filename, timestamp));

    samples_map_[token] = samples_vec_.back();
    if (!prev_token.empty()) {
      const auto& prev_sample = samples_map_.at(prev_token).lock();
      prev_sample->next_sample = samples_vec_.back();
      samples_vec_.back()->prev_sample = prev_sample;
    }
    if (!next_token.empty()) {
      const auto& next_sample = samples_map_.at(next_token).lock();
      next_sample->prev_sample = samples_vec_.back();
      samples_vec_.back()->next_sample = next_sample;
    }
  }

  bool is_complete() const noexcept { return waiting_list_.empty(); }

  size_t size() const noexcept { return samples_vec_.size(); }

  auto begin() noexcept { return samples_vec_.begin(); }
  auto end() noexcept { return samples_vec_.end(); }
  
  auto begin() const noexcept { return samples_vec_.cbegin(); }
  auto end() const noexcept { return samples_vec_.cend(); }
  
  auto cbegin() const noexcept { return samples_vec_.cbegin(); }
  auto cend() const noexcept { return samples_vec_.cend(); }

private:
  void parse_json_(const nlohmann::json& data, const std::unordered_set<std::string>& sample_tokens)
  {
    samples_vec_.reserve(data.size());
    for (const auto& item : data) {
      const auto item_sample_token = item.at(SAMPLE_FIELD_SAMPLE_TOKEN).get<std::string>();
      if (sample_tokens.find(item_sample_token) == sample_tokens.end()) {
        continue;
      }
      auto prev_token = item.at(SAMPLE_FIELD_PREV).get<std::string>();
      if (!prev_token.empty() && (samples_map_.find(prev_token) == samples_map_.end())) {
        waiting_list_.insert(std::move(prev_token));
      }
      auto next_token = item.at(SAMPLE_FIELD_NEXT).get<std::string>();
      if (!next_token.empty() && (samples_map_.find(next_token) == samples_map_.end())) {
        waiting_list_.insert(std::move(next_token));
      }
      const auto token = item.at(SAMPLE_FIELD_TOKEN).get<std::string>();
      if (waiting_list_.find(token) != waiting_list_.end()){
        waiting_list_.erase(token);
      }
      this->add_sample(token, item_sample_token,
        item.at(SAMPLE_FIELD_EGO_POSE_TOKEN).get<std::string>(),
        item.at(SAMPLE_FIELD_CALIBRATED_SENSOR_TOKEN).get<std::string>(),
        item.at(SAMPLE_FIELD_FILEFORMAT).get<std::string>(),
        item.at(SAMPLE_FIELD_FILENAME).get<std::string>(),
        item.at(SAMPLE_FIELD_TIMESTAMP).get<uint64_t>(),
        prev_token, next_token);
      // Next token will be linked when its sample is added
    }
    samples_vec_.shrink_to_fit();
  }

private:
  std::unordered_set<std::string> waiting_list_;
  std::vector<DataSample::SPtr> samples_vec_;
  std::unordered_map<std::string, DataSample::WPtr> samples_map_;
};

}
