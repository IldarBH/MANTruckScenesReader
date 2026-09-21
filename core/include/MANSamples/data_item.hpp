#pragma once
#include "MANTruckDataset/utils.hpp"

#include <memory>
#include <iostream>

namespace man::dataset::samples {

class DataItem {
public:
  using SPtr = std::shared_ptr<DataItem>;
  using WPtr = std::weak_ptr<DataItem>;

  DataItem(const Token& token, 
           const Token& sample_token, 
           const Token& ego_pose_token, 
           const Token& calibrated_sensor_token, 
           const std::string& fileformat, 
           const std::string& filename, 
           const uint64_t timestamp, 
           DataItem* prev_sample = nullptr, 
           DataItem* next_sample = nullptr);

  const auto& get_token() const noexcept { return TOKEN_; }
  const auto& get_sample_token() const noexcept { return SAMPLE_TOKEN_; }
  const auto& get_filename() const noexcept { return FILENAME_; }
  const auto& get_ego_pose_token() const noexcept { return EGO_POSE_TOKEN_; }
  const auto& get_calibrated_sensor_token() const noexcept { return CALIBRATED_SENSOR_TOKEN_; }
  const auto& get_timestamp() const noexcept { return TIMESTAMP_; }
  const auto& get_fileformat() const noexcept { return FILEFORMAT_; }

  friend std::ostream& operator<<(std::ostream& os, const DataItem& s);
private:
  const Token TOKEN_;
  const Token SAMPLE_TOKEN_;
  const Token EGO_POSE_TOKEN_;
  const Token CALIBRATED_SENSOR_TOKEN_;
  const std::string FILEFORMAT_;
  const std::string FILENAME_;
  const uint64_t TIMESTAMP_;
  DataItem* prev_sample_;
  DataItem* next_sample_;
};

}