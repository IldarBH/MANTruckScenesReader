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

class SampleSequence {
public:
  SampleSequence() = default;

  void read_samples(const std::string& filename, const Token& scene_token);

  void add_sample(const Token& token, const Token& scene_token, const int64_t timestamp, 
                  const Token& prev_token = {}, const Token& next_token = {});
  
  std::vector<Token> get_tokens() const noexcept;

  size_t size() const noexcept { return samples_vec_.size(); }
  auto begin() noexcept { return samples_vec_.begin(); }
  auto end() noexcept { return samples_vec_.end(); }
  auto cbegin() const noexcept { return samples_vec_.cbegin(); }
  auto cend() const noexcept { return samples_vec_.cend(); }
  const Sample& operator[](std::size_t index) const;

private:
  std::vector<Sample::SPtr> samples_vec_;
  std::unordered_map<Token, Sample::WPtr> samples_map_;
};
}
