#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <memory>

namespace man::dataset::samples {

class Sample {
public:
  using UPtr = std::unique_ptr<Sample>;
  using SPtr = std::shared_ptr<Sample>;
  using WPtr = std::weak_ptr<Sample>;

  Sample(const std::string& token, const std::string& filename, Sample::SPtr _prev = nullptr, Sample::SPtr const _next = nullptr)
  : TOKEN_(token), FILENAME_(filename), prev_sample(_prev), next_sample(_next) {}

  const std::string& get_filename() const noexcept { return FILENAME_; }

  std::string get_description() const noexcept
  {
    std::stringstream ss;
    ss << "Sample token: " << TOKEN_;
    if (prev_sample.lock())
      ss << "\n\tPrev: " << prev_sample.lock()->TOKEN_;
    if (next_sample.lock())
      ss << "\n\tNext: " << next_sample.lock()->TOKEN_;
    ss << "\n\tFilename: " << FILENAME_;
    return ss.str();
  }

public:
  WPtr prev_sample;
  WPtr next_sample;
private:
  const std::string TOKEN_;
  const std::string FILENAME_;
};

void print_samples_chain(const Sample& start_sample){
  for (Sample const* iter = &start_sample; iter; iter = iter->next_sample.lock().get()){
    std::cout << iter->get_description() << std::endl;
  }
}
};
