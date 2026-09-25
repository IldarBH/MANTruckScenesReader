#pragma once
#include "MANTruckDataset/utils.hpp"
#include "MANScenes/scene.hpp"

#include <memory>
#include <iostream>
#include <functional>

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

  const Token TOKEN;
  const Token SCENE_TOKEN;
  const int64_t TIMESTAMP;

private:
  void set_prev_sample_(Sample* prev) noexcept;
  void set_next_sample_(Sample* next) noexcept;

  Sample* prev_sample_ = nullptr;
  Sample* next_sample_ = nullptr;
};

struct SampleHash {
  using is_transparent = void;

  size_t operator()(const Sample::SPtr& Sample) const noexcept {
    return std::hash<man::dataset::Token>()(Sample->TOKEN);
  }

  size_t operator()(const Token& token) const noexcept {
    return std::hash<man::dataset::Token>()(token);
  }
};

struct SampleEqual {
  using is_transparent = void;

  bool operator()(const Sample::SPtr& lhs, const Sample::SPtr& rhs) const noexcept {
    return lhs->TOKEN == rhs->TOKEN;
  }

  bool operator()(const Sample::SPtr& lhs, const Token& rhs) const noexcept {
    return lhs->TOKEN == rhs;
  }

  bool operator()(const Token& lhs, const Sample::SPtr& rhs) const noexcept {
    return lhs == rhs->TOKEN;
  }
};

inline std::ostream& operator<<(std::ostream& os, const Sample& sample)
{
  os << "Sample:"
     << "\n\tToken: " << sample.TOKEN
     << "\n\tScene token: " << sample.SCENE_TOKEN
     << "\n\tTimestamp: " << sample.TIMESTAMP;
  return os;
}

} // namespace man::dataset::samples