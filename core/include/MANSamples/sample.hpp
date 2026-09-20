#pragma once
#include "MANTruckDataset/utils.hpp"

#include <memory>
#include <iostream>

namespace man::dataset::samples {

class Sample {
public:
  using SPtr = std::shared_ptr<Sample>;
  using WPtr = std::weak_ptr<Sample>;
  
  Sample() = delete;
  
  Sample(const Token& token, 
         const Token& scene_token, 
         const int64_t timestamp, 
         Sample* prev_sample = nullptr, 
         Sample* next_sample = nullptr);
  
  Sample(const Sample& other);

  ~Sample();
  
  Sample& operator=(const Sample& other) = delete;

  const auto& get_token() const noexcept { return TOKEN_; }
  const auto& get_scene_token() const noexcept { return SCENE_TOKEN_; }
  const auto& get_timestamp() const noexcept { return TIMESTAMP_; }

  friend std::ostream& operator<<(std::ostream& os, const Sample& sample);

private:
  void set_prev_sample_(Sample* prev) noexcept;
  void set_next_sample_(Sample* next) noexcept;

  const Token TOKEN_;
  const Token SCENE_TOKEN_;
  const int64_t TIMESTAMP_;
  Sample* prev_sample_ = nullptr;
  Sample* next_sample_ = nullptr;
};

std::ostream& operator<<(std::ostream& os, const Sample& sample);

} // namespace man::dataset::samples