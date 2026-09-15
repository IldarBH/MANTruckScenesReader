#pragma once
#include "MANSensors/sensor.hpp"
#include "MANTruckDataset/utils.hpp"

#include <string>
#include <sstream>
#include <iostream>
#include <string_view>
#include <set>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <memory>

namespace man::dataset::sensors {

class DataItem {
public:
  using SPtr = std::shared_ptr<DataItem>;
  using WPtr = std::weak_ptr<DataItem>;

  DataItem(const size_t timestamp, 
           const std::string& filename, 
           const DataItem* prev = nullptr, 
           const DataItem* next = nullptr);

  const size_t get_timestamp() const noexcept { return TIMESTAMP_; }
  const std::string& get_filename() const noexcept { return FILENAME_; }
  DataItem* get_prev_sample() const noexcept { return prev_sample_; }
  DataItem* get_next_sample() const noexcept { return next_sample_; }
  void set_prev_sample(DataItem* prev) noexcept;
  void set_next_sample(DataItem* next) noexcept;
  
  friend bool operator<(const DataItem& a, const DataItem& b);

private:
  const size_t TIMESTAMP_;
  const std::string FILENAME_;

  DataItem* prev_sample_ = nullptr;
  DataItem* next_sample_ = nullptr;
};

inline bool operator<(const DataItem& a, const DataItem& b) {return a.TIMESTAMP_ < b.TIMESTAMP_; }

inline bool operator<(const DataItem::SPtr& a, const DataItem::SPtr& b) {return *a < *b; }

}
