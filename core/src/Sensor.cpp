#include "MANTruckDataset/Sensor.hpp"

namespace man::dataset::sensors {

namespace {
  constexpr std::string_view TOKEN_KEY = "token";
  constexpr std::string_view MODALITY_KEY = "modality";
  constexpr std::string_view CHANNEL_KEY = "channel";
  constexpr std::string_view LIDAR_MODALITY = "lidar";
}

DataItem::DataItem(const size_t timestamp, const std::string& filename, const DataItem* prev = nullptr, const DataItem* next = nullptr)
  : TIMESTAMP_(timestamp), FILENAME_(filename)
{}

void DataItem::set_prev_sample(DataItem* prev) noexcept 
{
  if (prev == this) {
    #ifdef DEBUG
      std::cerr << "Warning: Attempted to set previous sample to self for DataItem with timestamp " << TIMESTAMP_ << "\n";
    #endif
    return;
  };
  prev_sample_ = prev;
  if (prev && (prev->get_next_sample() != this))
    prev->set_next_sample(this);
}

void DataItem::set_next_sample(DataItem* next) noexcept 
{ 
  if (next == this) {
    #ifdef DEBUG
      std::cerr << "Warning: Attempted to set next sample to self for DataItem with timestamp " << TIMESTAMP_ << "\n";
    #endif
    return;
  };
  next_sample_ = next;
  if (next && (next->get_prev_sample() != this))
    next->set_prev_sample(this);
}

SensorBase::SensorBase(const Token& token, const std::string& channel, const std::string_view modality)
  : TOKEN_(token), CHANNEL_(channel), MODALITY_(modality)
{}

SensorBase::SensorBase(const std::string& token, const std::string& channel, const std::string_view modality)
  : SensorBase(Token(token), channel, modality)
{}

void SensorBase::add_file(const std::string& filename, const size_t timestamp) 
{ 
  if (samples_vec_.empty()){
    samples_vec_.emplace_back(std::make_shared<DataItem>(timestamp, filename));
  } else {
    const auto& last_sample = samples_vec_.back();
    auto new_sample = std::make_shared<DataItem>(timestamp, filename, last_sample.get());
    samples_vec_.emplace_back(std::move(new_sample));
  }
}

const DataItem SensorBase::operator[](const size_t index) const 
{ 
  if (index >= samples_vec_.size()) {
    throw std::out_of_range("Index " + std::to_string(index) + " out of range.");
  }
  return *samples_vec_[index]; 
}

std::ostream& operator<<(std::ostream& os, const SensorBase& sensor)
{
  os << "Sensor:\n\tToken: " << sensor.TOKEN_ << "\n\tChannel: " << sensor.CHANNEL_ 
     << "\n\tModality: " << sensor.MODALITY_ << "\n\tFiles cound: " << sensor.samples_vec_.size();
  return os;
}

void SensorManager::read_sensors(const std::string& filename, const std::vector<Token>& filter_tokens = {})
{
  const std::unordered_set<Token> filter_set(filter_tokens.begin(), filter_tokens.end());
  const auto json_file = read_json_file(filename);
  this->parse_json_(json_file, filter_set);
}

void SensorManager::add_sensor(const Token& token, const std::string& channel, const std::string& modality)
{
  auto sensor = std::make_shared<SensorBase>(token, channel, modality);
  sensors_vec_.emplace_back(sensor);                  // Index based access
  sensors_by_token_[token] = sensor;                  // Index by token
}

SensorBase& SensorManager::operator[](const Token& token)
{
  const auto iter = sensors_by_token_.find(token);
  if (iter == sensors_by_token_.end()) {
    throw std::runtime_error("Sensor with token " + token.value + " not found.");
  }
  return *(iter->second);
}

const SensorBase& SensorManager::operator[](const Token& token) const
{
  const auto iter = sensors_by_token_.find(token);
  if (iter == sensors_by_token_.end()) {
    throw std::runtime_error("Sensor with token " + token.value + " not found.");
  }
  return *(iter->second);
}

void SensorManager::parse_json_(const nlohmann::json& data, const std::unordered_set<Token>& filter_tokens)
{
  for (const auto& item : data) {
    const Token token(item.at(TOKEN_KEY).get<std::string>());
    const std::string channel(item.at(CHANNEL_KEY).get<std::string>());
    const std::string modality(item.at(MODALITY_KEY).get<std::string>());
    if (!filter_tokens.empty() && (filter_tokens.find(token) != filter_tokens.end())) {
      add_sensor(token, channel, modality);
    }
  }
}

}