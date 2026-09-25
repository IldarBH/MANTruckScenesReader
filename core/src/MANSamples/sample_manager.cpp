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

  constexpr std::string_view SAMPLE_FIELD_SAMPLE_TOKEN = "sample_token";
  constexpr std::string_view SAMPLE_FIELD_EGO_POSE_TOKEN = "ego_pose_token";
  constexpr std::string_view SAMPLE_FIELD_CALIBRATED_SENSOR_TOKEN = "calibrated_sensor_token";
  constexpr std::string_view SAMPLE_FIELD_FILEFORMAT = "fileformat";
  constexpr std::string_view SAMPLE_FIELD_FILENAME = "filename";
}

size_t SampleManager::read_samples(const std::string& filename)
{
  return this->read_samples(filename, {});
}

size_t SampleManager::read_samples(const std::string& filename, const scenes::SceneSet& scenes)
{
  samples_.clear();
  const auto data = read_json_file(filename);
  samples_.reserve(data.size());
  for (const auto& item : data) {
    const Token token(item.at(SAMPLE_FIELD_TOKEN).get<std::string>());
    const Token scene_token(item.at(SAMPLE_FIELD_SCENE_TOKEN).get<std::string>());
    const Token prev_token(item.at(SAMPLE_FIELD_PREV).get<std::string>());
    const Token next_token(item.at(SAMPLE_FIELD_NEXT).get<std::string>());
    const size_t timestamp = item.at(SAMPLE_FIELD_TIMESTAMP).get<int64_t>();
    this->add_sample_(token, scene_token, timestamp, prev_token, next_token);
  }
  return samples_.size();
}

size_t SampleManager::read_samples_data(const std::string& filename)
{
  data_items_vec_.clear();
  data_items_by_token_.clear();
  data_items_by_sample_token_.clear();
  const auto data = read_json_file(filename);
  data_items_vec_.reserve(data.size());
  data_items_by_token_.reserve(data.size());
  data_items_by_sample_token_.reserve(data.size());
  this->parse_data_items_(data);
  return data_items_vec_.size();
}

void SampleManager::add_sample_(const Token& token, const Token& scene_token, const int64_t timestamp, 
  const Token& prev_token, const Token& next_token)
{
  if (samples_.find(token) != samples_.end()) {
    throw std::invalid_argument("Sample with token " + token.value + " already exists.");
  }

  Sample* prev_sample = nullptr;
  if (!prev_token.value.empty()) {
    if (const auto& iter = samples_.find(prev_token); iter != samples_.end()) {
      prev_sample = iter->get();
    }
  }
  Sample* next_sample = nullptr;
  if (!next_token.value.empty()) {
    if (const auto& iter = samples_.find(next_token); iter != samples_.end()) {
      next_sample = iter->get();
    }
  }

  samples_.emplace(std::make_shared<Sample>(token, scene_token, timestamp, prev_sample, next_sample));
}

void SampleManager::add_data_item_(const Token& token, const Token& sample_token, const Token& ego_pose_token, const Token& calibrated_sensor_token,
  const std::string& fileformat, const std::string& filename, const uint64_t timestamp, const Token& prev_token, const Token& next_token)
{
  if (data_items_by_token_.find(token) != data_items_by_token_.end()) {
    throw std::invalid_argument("DataItem with token " + token.value + " already exists.");
  }

  DataItem* prev_data_item = nullptr;
  if (!prev_token.value.empty()) {
    if (const auto& iter = data_items_by_token_.find(prev_token); iter != data_items_by_token_.end()) {
      prev_data_item = iter->second.get();
    }
  }
  DataItem* next_data_item = nullptr;
  if (!next_token.value.empty()) {
    if (const auto& iter = data_items_by_token_.find(next_token); iter != data_items_by_token_.end()) {
      next_data_item = iter->second.get();
    }
  }

  data_items_vec_.emplace_back(std::make_shared<DataItem>(token, sample_token, ego_pose_token, calibrated_sensor_token, 
    fileformat, filename, timestamp, prev_data_item, next_data_item));
  data_items_by_token_.emplace(std::make_pair(token, data_items_vec_.back()));
  if (auto iter = data_items_by_sample_token_.find(sample_token); iter == data_items_by_sample_token_.end()) {
    data_items_by_sample_token_[sample_token] = {data_items_vec_.back()};
  } else {
    iter->second.push_back(data_items_vec_.back());
  }
}

void SampleManager::parse_data_items_(const nlohmann::json& data)
{
  for (const auto& item : data) {
    const Token token(item.at(SAMPLE_FIELD_TOKEN).get<std::string>());
    const Token sample_token(item.at(SAMPLE_FIELD_SAMPLE_TOKEN).get<std::string>());
    const Token ego_pose_token(item.at(SAMPLE_FIELD_EGO_POSE_TOKEN).get<std::string>());
    const Token calibrated_sensor_token(item.at(SAMPLE_FIELD_CALIBRATED_SENSOR_TOKEN).get<std::string>());
    const std::string fileformat(item.at(SAMPLE_FIELD_FILEFORMAT).get<std::string>());
    const std::string filename(item.at(SAMPLE_FIELD_FILENAME).get<std::string>());
    const uint64_t timestamp(item.at(SAMPLE_FIELD_TIMESTAMP).get<int64_t>());
    const Token prev_token(item.at(SAMPLE_FIELD_PREV).get<std::string>());
    const Token next_token(item.at(SAMPLE_FIELD_NEXT).get<std::string>());
    this->add_data_item_(token, sample_token, ego_pose_token, calibrated_sensor_token, fileformat, filename, timestamp, prev_token, next_token);
  }
}

}