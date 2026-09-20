#include "MANSamples/sample_manager.hpp"
#include "MANSamples/sample.hpp"
#include "MANTruckDataset/utils.hpp"

namespace man::dataset::samples {

namespace {
  constexpr std::string_view SAMPLE_FIELD_TOKEN = "token";
  constexpr std::string_view SAMPLE_FIELD_SCENE_TOKEN = "scene_token";
  constexpr std::string_view SAMPLE_FIELD_TIMESTAMP = "timestamp";
  constexpr std::string_view SAMPLE_FIELD_PREV = "prev";
  constexpr std::string_view SAMPLE_FIELD_NEXT = "next";
}

size_t SampleManager::read_samples(const std::string& filename)
{
  samples_vec_.clear();
  samples_by_token_.clear();
  samples_by_scene_token_.clear();
  const auto data = read_json_file(filename);
  samples_vec_.reserve(data.size());
  samples_by_token_.reserve(data.size());
  samples_by_scene_token_.reserve(data.size());
  for (const auto& item : data) {
    const Token item_scene_token(item.at(SAMPLE_FIELD_SCENE_TOKEN).get<std::string>());
    const Token sample_token(item.at(SAMPLE_FIELD_TOKEN).get<std::string>());
    const Token prev_token(item.at(SAMPLE_FIELD_PREV).get<std::string>());
    const Token next_token(item.at(SAMPLE_FIELD_NEXT).get<std::string>());
    const size_t timestamp = item.at(SAMPLE_FIELD_TIMESTAMP).get<int64_t>();
    this->add_sample_(sample_token, item_scene_token, timestamp, prev_token, next_token);
  }
  return samples_vec_.size();
}


void SampleManager::add_sample_(const Token& token, const Token& scene_token, const int64_t timestamp, 
  const Token& prev_token, const Token& next_token)
{
  if (samples_by_token_.find(token) != samples_by_token_.end()) {
    throw std::invalid_argument("Sample with token " + token.value + " already exists.");
  }

  Sample* prev_sample = nullptr;
  if (!prev_token.value.empty()) {
    if (const auto& iter = samples_by_token_.find(prev_token); iter != samples_by_token_.end()) {
      prev_sample = iter->second.get();
    }
  }
  Sample* next_sample = nullptr;
  if (!next_token.value.empty()) {
    if (const auto& iter = samples_by_token_.find(next_token); iter != samples_by_token_.end()) {
      next_sample = iter->second.get();
    }
  }

  samples_vec_.emplace_back(std::make_shared<Sample>(token, scene_token, timestamp, prev_sample, next_sample));
  samples_by_token_.emplace(std::make_pair(token, samples_vec_.back()));
  if (auto iter = samples_by_scene_token_.find(scene_token); iter == samples_by_scene_token_.end()) {
    samples_by_scene_token_[scene_token] = {samples_vec_.back()};
  } else {
    iter->second.push_back(samples_vec_.back());
  }
}

}