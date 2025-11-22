#pragma once
#include "MANTruckDataset/utils.hpp"

#include <string>
#include <string_view>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <stdexcept>

namespace man::dataset::samples {

class Sample {
public:
  using SPtr = std::shared_ptr<Sample>;
  using WPtr = std::weak_ptr<Sample>;

  Sample(
    const std::string& token, 
    const std::string& scene_token, 
    const int64_t timestamp)
    : TOKEN_(token)
    , SCENE_TOKEN_(scene_token)
    , TIMESTAMP_(timestamp)
    {}
    
    const std::string& get_token() const noexcept { return TOKEN_; }
    const std::string& get_scene_token() const noexcept { return SCENE_TOKEN_; }
    int64_t get_timestamp() const noexcept { return TIMESTAMP_; }
    
    bool operator<(const Sample& other) const {return TIMESTAMP_ < other.TIMESTAMP_;}
    
    friend std::ostream& operator<<(std::ostream& os, const Sample& sample);
public:
  WPtr prev_sample;
  WPtr next_sample;
private:
  const std::string TOKEN_;
  const std::string SCENE_TOKEN_;
  const int64_t TIMESTAMP_;
};

inline std::ostream& operator<<(std::ostream& os, const Sample& sample) {
  os << "Sample:\n"
     << "\tToken: " << sample.TOKEN_ << "\n"
     << "\tScene token: " << sample.SCENE_TOKEN_ << "\n"
     << "\tTimestamp: " << sample.TIMESTAMP_;
  return os;
}

namespace {
constexpr std::string_view SAMPLE_FIELD_TOKEN = "token";
constexpr std::string_view SAMPLE_FIELD_SCENE_TOKEN = "scene_token";
constexpr std::string_view SAMPLE_FIELD_TIMESTAMP = "timestamp";
constexpr std::string_view SAMPLE_FIELD_PREV = "prev";
constexpr std::string_view SAMPLE_FIELD_NEXT = "next";
}

class SampleSequence {
public:
  SampleSequence() = default;

  void read_samples(const std::string& filename, const std::string& scene_token)
  {
    const auto data = read_json_file(filename);
    for (const auto& item : data) {
      const auto item_scene_token = item.at(SAMPLE_FIELD_SCENE_TOKEN).get<std::string>();
      if (item_scene_token != scene_token) {
        continue;
      }
      this->add_sample(
        item.at(SAMPLE_FIELD_TOKEN).get<std::string>(),
        item.at(SAMPLE_FIELD_SCENE_TOKEN).get<std::string>(),
        item.at(SAMPLE_FIELD_TIMESTAMP).get<int64_t>(),
        item.at(SAMPLE_FIELD_PREV).get<std::string>());
      // Next token will be linked when its sample is added
    }
  }

  void add_sample(
    const std::string& token, 
    const std::string& scene_token,
    const int64_t timestamp, 
    const std::string& prev_token = "",
    const std::string& next_token = "")
  {
    if (samples_map_.find(token) != samples_map_.end()) {
      throw std::invalid_argument("Sample with token " + token + " already exists.");
    }
    samples_vec_.emplace_back(std::make_shared<Sample>(token, scene_token, timestamp));
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

  size_t size() const noexcept { return samples_vec_.size(); }

  auto begin() noexcept { return samples_vec_.begin(); }
  auto end() noexcept { return samples_vec_.end(); }
  
  auto begin() const noexcept { return samples_vec_.cbegin(); }
  auto end() const noexcept { return samples_vec_.cend(); }
  
  auto cbegin() const noexcept { return samples_vec_.cbegin(); }
  auto cend() const noexcept { return samples_vec_.cend(); }

  const Sample& operator[](std::size_t index) const { return *samples_vec_.at(index); }
private:
  std::vector<Sample::SPtr> samples_vec_;
  std::unordered_map<std::string, Sample::WPtr> samples_map_;
};
}
