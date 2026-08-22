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
  
  Sample() = delete;
  
  Sample(
    const Token& token, 
    const Token& scene_token, 
    const int64_t timestamp,
    Sample* prev_sample = nullptr,
    Sample* next_sample = nullptr);
  
  Sample(const Sample& other);

  ~Sample();
  
  Sample& operator=(const Sample& other) = delete;

  void set_prev_sample(Sample* prev) noexcept;
  void set_next_sample(Sample* next) noexcept;
  const auto& get_token() const noexcept { return TOKEN_; }
  const auto& get_scene_token() const noexcept { return SCENE_TOKEN_; }
  const int64_t& get_timestamp() const noexcept { return TIMESTAMP_; }
  Sample* get_prev_sample() const noexcept { return prev_sample_; }
  Sample* get_next_sample() const noexcept { return next_sample_; }

  friend std::ostream& operator<<(std::ostream& os, const Sample& sample);

private:
  const Token TOKEN_;
  const Token SCENE_TOKEN_;
  const int64_t TIMESTAMP_;
  Sample* prev_sample_ = nullptr;
  Sample* next_sample_ = nullptr;
};

std::ostream& operator<<(std::ostream& os, const Sample& sample);

class SampleManager {
public:
  SampleManager() = default;

  /**
   * @brief Read samples from a json file and add them to the manager.
   * Clear existing samples before reading.
   * @param filename Path to the CSV file.
   * @param scene_token Token of the scene to which the samples belong.
   */
  void read_samples(const std::string& filename);

  /**
   * @brief Add a sample to the manager.
   * @param token Token of the sample.
   * @param scene_token Token of the scene to which the sample belongs.
   * @param timestamp Timestamp of the sample.
   * @param prev_token Token of the previous sample (optional).
   * @param next_token Token of the next sample (optional).
   */
  void add_sample(const Token& token, const Token& scene_token, const int64_t timestamp, 
                  const Token& prev_token = {}, const Token& next_token = {});
  
  /**
   * @brief Get vector of all sample tokens managed.
   */
  const auto& get_samples() const noexcept { return samples_vec_; }
  
  const Sample& operator[](std::size_t index) const;
  auto begin() noexcept { return samples_vec_.begin(); }
  auto end() noexcept { return samples_vec_.end(); }
  auto cbegin() const noexcept { return samples_vec_.cbegin(); }
  auto cend() const noexcept { return samples_vec_.cend(); }
  size_t size() const noexcept { return samples_vec_.size(); }

private:
  std::vector<Sample::SPtr> samples_vec_;
  std::unordered_map<Token, Sample::WPtr> samples_map_;
};
}
