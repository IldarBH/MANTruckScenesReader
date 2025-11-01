#pragma once
#include <string>
#include <sstream>

template <typename DataType>
class SensorBase {
public:
  SensorBase(const std::string token, const std::string channel, const std::string_view modality)
  : TOKEN_(token)
  , CHANNEL_(channel)
  , MODALITY_(modality)
  {
  }

  virtual DataType operator[](const size_t index) const = 0;

  std::string get_description() const 
  {
    std::stringstream ss;
    ss << "Sensor: " << "\n\tToken: " << TOKEN_ << "\n\tChannel: " << CHANNEL_ << "\n\tModality: " << MODALITY_;
    return ss.str();
  }

private:
  const std::string TOKEN_;
  const std::string CHANNEL_;
  const std::string MODALITY_;
};
