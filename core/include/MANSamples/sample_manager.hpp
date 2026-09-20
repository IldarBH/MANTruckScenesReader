#pragma once
#include "MANTruckDataset/utils.hpp"
#include "MANSamples/sample.hpp"

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

namespace man::dataset::samples {

class SampleManager {
public:
  SampleManager() = default;

  /**
   * @brief Read samples from a json file and add them to the manager.
   * Clear existing samples before reading.
   * @param filename Path to the CSV file.
   * @return Number of samples read.
   */
  size_t read_samples(const std::string& filename);
  
  auto begin() noexcept { return samples_vec_.begin(); }
  auto end() noexcept { return samples_vec_.end(); }
  auto cbegin() const noexcept { return samples_vec_.cbegin(); }
  auto cend() const noexcept { return samples_vec_.cend(); }
  size_t size() const noexcept { return samples_vec_.size(); }

private:
  void add_sample_(const Token& token, 
                   const Token& scene_token, 
                   const int64_t timestamp, 
                   const Token& prev_token, 
                   const Token& next_token);

  std::vector<Sample::SPtr> samples_vec_;
  std::unordered_map<Token, Sample::SPtr> samples_by_token_;
  std::unordered_map<Token, std::vector<Sample::SPtr>> samples_by_scene_token_;
};
}
