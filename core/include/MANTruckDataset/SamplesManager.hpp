#pragma once

#include "MANTruckDataset/Sample.hpp"
#include "MANTruckDataset/utils.hpp"

#include <string>
#include <string_view>
#include <iostream>
#include <unordered_map>
#include <memory>

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

  size_t read_samples(const std::string& filename)
  {
    const auto data = read_json_file(filename);
    samples_.reserve(data.size());
    for (const auto& item : data) {
      this->add_sample(item.at(TOKEN_KEY).get<std::string>(), item.at(FILENAME_KEY).get<std::string>());
    }
    return samples_.size();
  }

  void add_sample(const std::string& token, const std::string& filename)
  {
    if (samples_.empty()) {
      samples_.emplace_back(std::make_shared<Sample>(token, filename));
    } else {
      auto sample = std::make_shared<Sample>(token, filename, samples_.back());
      samples_.back()->next_sample = sample;
      samples_.emplace_back(std::move(sample));
    }
  }

  size_t size() const noexcept { return samples_.size(); };

  const Sample& operator[](const size_t index) const { return *samples_[index]; };
private:
  std::vector<Sample::SPtr> samples_;
};
}
