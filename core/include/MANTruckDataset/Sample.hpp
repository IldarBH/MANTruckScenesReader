#pragma once

#include <string>
#include <iostream>
#include <memory>

namespace man::dataset::samples {
  
class Sample {
public:
  using UPtr = std::unique_ptr<Sample>;
  using SPtr = std::shared_ptr<Sample>;
  using WPtr = std::weak_ptr<Sample>;

  Sample(const std::string& token, const std::string& filename, SPtr _prev = nullptr, SPtr _next = nullptr)
  : TOKEN_(token), FILENAME_(filename), prev_sample(_prev), next_sample(_next) {}

  const std::string& get_filename() const noexcept { return FILENAME_; }

  friend std::ostream& operator<<(std::ostream& os, const Sample& s);

public:
  WPtr prev_sample;
  WPtr next_sample;
private:
  const std::string TOKEN_;
  const std::string FILENAME_;
};

inline std::ostream& operator<<(std::ostream& os, const Sample& s) { 
  os << "Sample token: " << s.TOKEN_;
  if (auto prev = s.prev_sample.lock())
    os << "\n\tPrev: " << prev->TOKEN_;
  if (auto next = s.next_sample.lock())
    os << "\n\tNext: " << next->TOKEN_;
  os << "\n\tFilename: " << s.FILENAME_;
  return os;
}

inline void print_samples_chain(const Sample::SPtr& start_sample) {
  for (auto cur = start_sample; cur; cur = cur->next_sample.lock()) {
    std::cout << *cur << std::endl;
  }
}
}
