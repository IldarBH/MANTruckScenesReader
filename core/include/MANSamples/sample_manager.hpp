#pragma once
#include "MANTruckDataset/utils.hpp"
#include "MANSamples/sample.hpp"
#include "MANSamples/data_item.hpp"

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <nlohmann/json.hpp>

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

  /**
   * @brief Read sample data from a CSV file and add them to the manager.
   * Clear existing samples before reading.
   * @param filename Path to the CSV file.
   * @return Number of samples read.
   */
  size_t read_samples_data(const std::string& filename);
  
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
  void add_data_item_(const Token& token, 
                      const Token& sample_token, 
                      const Token& ego_pose_token, 
                      const Token& calibrated_sensor_token,
                      const std::string& fileformat, 
                      const std::string& filename, 
                      const uint64_t timestamp, 
                      const Token& prev_token, 
                      const Token& next_token);
  void parse_samples_(const nlohmann::json& data);
  void parse_data_items_(const nlohmann::json& data);


  std::vector<Sample::SPtr> samples_vec_;
  std::unordered_map<Token, Sample::SPtr> samples_by_token_;
  std::unordered_map<Token, std::vector<Sample::SPtr>> samples_by_scene_token_;

  std::vector<DataItem::SPtr> data_items_vec_;
  std::unordered_map<Token, DataItem::SPtr> data_items_by_token_;
  std::unordered_map<Token, std::vector<DataItem::SPtr>> data_items_by_sample_token_;
};
}
