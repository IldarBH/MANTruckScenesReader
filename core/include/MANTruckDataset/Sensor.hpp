#pragma once
#include <string>

template <typename DataType>
class SensorBase {
public:
  SensorBase(const std::string token, const std::string channel)
  : TOKEN_(token)
  , CHANNEL_(token)
  {

  }

  virtual DataType operator[](const size_t index) const = 0;

private:
  const std::string TOKEN_;
  const std::string CHANNEL_;
};
