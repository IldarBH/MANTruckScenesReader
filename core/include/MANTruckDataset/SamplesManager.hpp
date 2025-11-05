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
    const auto& s_iter = data.cbegin();
    samples_.emplace_back(std::make_shared<Sample>(
      s_iter->at(TOKEN_KEY).get<std::string>(), s_iter->at(FILENAME_KEY).get<std::string>()));
    for (auto iter = std::next(s_iter); iter != data.cend(); iter = std::next(iter)) {
      auto sample = std::make_shared<Sample>(
        iter->at(TOKEN_KEY).get<std::string>(), iter->at(FILENAME_KEY).get<std::string>(), samples_.back());
      samples_.back()->next_sample = sample;
      samples_.emplace_back(std::move(sample));
    }
    return samples_.size();
  }

  size_t size() const noexcept { return samples_.size(); };

  const Sample& operator[](const size_t index) const { return *samples_[index]; };
private:
  std::vector<Sample::SPtr> samples_;
};
}
