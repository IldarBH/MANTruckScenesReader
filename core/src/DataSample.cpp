#include "MANTruckDataset/DataSample.hpp"

#include <string_view>

namespace man::dataset::data_samples {

namespace {
  constexpr std::string_view SAMPLE_FIELD_TOKEN = "token";
  constexpr std::string_view SAMPLE_FIELD_SAMPLE_TOKEN = "sample_token";
  constexpr std::string_view SAMPLE_FIELD_EGO_POSE_TOKEN = "ego_pose_token";
  constexpr std::string_view SAMPLE_FIELD_CALIBRATED_SENSOR_TOKEN = "calibrated_sensor_token";
  constexpr std::string_view SAMPLE_FIELD_TIMESTAMP = "timestamp";
  constexpr std::string_view SAMPLE_FIELD_FILEFORMAT = "fileformat";
  constexpr std::string_view SAMPLE_FIELD_FILENAME = "filename";
  constexpr std::string_view SAMPLE_FIELD_PREV = "prev";
  constexpr std::string_view SAMPLE_FIELD_NEXT = "next";
}

DataSample::DataSample(
  const Token& token, const Token& sample_token, const Token& ego_pose_token, const Token& calibrated_sensor_token, 
  const std::string& fileformat, const std::string& filename, const uint64_t timestamp, 
  const Token& prev_token, const Token& next_token)
  : TOKEN_(token)
  , SAMPLE_TOKEN_(sample_token)
  , EGO_POSE_TOKEN_(ego_pose_token)
  , CALIBRATED_SENSOR_TOKEN_(calibrated_sensor_token)
  , TIMESTAMP_(timestamp)
  , FILEFORMAT_(fileformat)
  , FILENAME_(filename)
  , PREV_TOKEN_(prev_token)
  , NEXT_TOKEN_(next_token) 
  {}

std::ostream& operator<<(std::ostream& os, const DataSample& sample) 
{
  os << "Data sample:\n"
     << "\tToken: " << sample.TOKEN_ << "\n"
     << "\tSample token: " << sample.SAMPLE_TOKEN_ << "\n"
     << "\tCalibrated sensor token: " << sample.CALIBRATED_SENSOR_TOKEN_ << "\n"
     << "\tTimestamp: " << sample.TIMESTAMP_ << "\n"
     << "\tFilename: " << sample.FILENAME_ ;
  return os;
}

void DataSequence::read_samples(const std::string& filename, const std::vector<Token>& sample_tokens)
{
  const auto data = read_json_file(filename);
  const std::unordered_set<Token> sorted_tokens(sample_tokens.begin(), sample_tokens.end());
  this->parse_json_(data, sorted_tokens);
}

void DataSequence::add_sample(
  const Token& token, const Token& sample_token, const Token& ego_pose_token, const Token& calibrated_sensor_token, 
  const std::string& fileformat, const std::string& filename, const uint64_t timestamp,
  const Token& prev_token, const Token& next_token)
{
  if (samples_map_.find(token) != samples_map_.end()) {
    throw std::invalid_argument("Sample with token " + token.value + " already exists.");
  }
  samples_vec_.emplace_back(std::make_shared<DataSample>(token, sample_token, ego_pose_token, calibrated_sensor_token, fileformat, filename, timestamp));
  samples_map_.emplace(std::make_pair(token, samples_vec_.back()));
  if (!prev_token.value.empty()) {
    const auto& prev_sample = samples_map_.at(prev_token).lock();
    prev_sample->next_sample = samples_vec_.back();
    samples_vec_.back()->prev_sample = prev_sample;
  }
  if (!next_token.value.empty()) {
    const auto& next_sample = samples_map_.at(next_token).lock();
    next_sample->prev_sample = samples_vec_.back();
    samples_vec_.back()->next_sample = next_sample;
  }
}

void DataSequence::parse_json_(const nlohmann::json& data, const std::unordered_set<Token>& sample_tokens)
{
  samples_vec_.reserve(data.size());
  for (const auto& item : data) {
    const auto item_sample_token = Token(item.at(SAMPLE_FIELD_SAMPLE_TOKEN).get<std::string>());
    if (sample_tokens.find(item_sample_token) == sample_tokens.end()) {
      continue;
    }
    auto prev_token = Token(item.at(SAMPLE_FIELD_PREV).get<std::string>());
    if (!prev_token.value.empty() && (samples_map_.find(prev_token) == samples_map_.end())) {
      waiting_list_.insert(std::move(prev_token));
    }
    auto next_token = Token(item.at(SAMPLE_FIELD_NEXT).get<std::string>());
    if (!next_token.value.empty() && (samples_map_.find(next_token) == samples_map_.end())) {
      waiting_list_.insert(std::move(next_token));
    }
    const auto token = Token(item.at(SAMPLE_FIELD_TOKEN).get<std::string>());
    if (waiting_list_.find(token) != waiting_list_.end()){
      waiting_list_.erase(token);
    }
    this->add_sample(token, item_sample_token,
      Token(item.at(SAMPLE_FIELD_EGO_POSE_TOKEN).get<std::string>()),
      Token(item.at(SAMPLE_FIELD_CALIBRATED_SENSOR_TOKEN).get<std::string>()),
      item.at(SAMPLE_FIELD_FILEFORMAT).get<std::string>(),
      item.at(SAMPLE_FIELD_FILENAME).get<std::string>(),
      item.at(SAMPLE_FIELD_TIMESTAMP).get<uint64_t>(),
      prev_token, next_token);
    // Next token will be linked when its sample is added
  }
  samples_vec_.shrink_to_fit();
}

}