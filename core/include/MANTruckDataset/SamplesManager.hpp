#pragma once

#include "MANTruckDataset/Sample.hpp"
#include "MANTruckDataset/utils.hpp"

#include <string>
#include <string_view>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <stdexcept>

namespace man::dataset::samples {

namespace {
  constexpr std::string_view TOKEN_KEY = "token";
  constexpr std::string_view FILENAME_KEY = "filename";
  constexpr std::string_view PREV_KEY = "prev";
  constexpr std::string_view NEXT_KEY = "next";
}

class SampleManager {
public:
  SampleManager() = default;

  void read_samples(const std::string& filename)
  {
    const auto data = read_json_file(filename);
    samples_vec_.reserve(data.size());
    samples_map_.reserve(data.size());
    for (const auto& item : data) {
      this->add_sample(item.at(TOKEN_KEY).get<std::string>(), item.at(FILENAME_KEY).get<std::string>());
    }
  }

  void add_sample(const std::string& token, const std::string& filename)
  {
    if (samples_vec_.empty()) {
      auto first_sample = std::make_shared<Sample>(token, filename);
      samples_vec_.emplace_back(first_sample);
      samples_map_[token] = first_sample;
    } else {
      auto sample = std::make_shared<Sample>(token, filename, samples_vec_.back());
      samples_vec_.back()->next_sample = sample;
      samples_vec_.emplace_back(sample);
      samples_map_[token] = sample;
    }
  }

  size_t size() const noexcept { return samples_vec_.size(); }

  const Sample& operator[](const size_t index) const { return *samples_vec_[index]; }

  const Sample& operator[](const std::string& token) const { 
    auto it = samples_map_.find(token);
    if (it == samples_map_.end())
      throw std::out_of_range("Token not found in samples_map_.");
    auto sample_p = it->second.lock();
    if (!sample_p)
      throw std::invalid_argument("Expired weak pointer for token: " + token);
    return *sample_p; 
  }

  auto begin() noexcept { return samples_vec_.begin(); }
  auto end() noexcept { return samples_vec_.end(); }
  
  auto begin() const noexcept { return samples_vec_.cbegin(); }
  auto end() const noexcept { return samples_vec_.cend(); }
  
  auto cbegin() const noexcept { return samples_vec_.cbegin(); }
  auto cend() const noexcept { return samples_vec_.cend(); }

private:
  std::vector<Sample::SPtr> samples_vec_;
  std::unordered_map<std::string, Sample::WPtr> samples_map_;
};
}
