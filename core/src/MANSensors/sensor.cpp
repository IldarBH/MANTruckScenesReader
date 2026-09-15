#include "MANSensors/sensor.hpp"
#include "MANSensors/modality.hpp"
#include "MANTruckDataset/utils.hpp"

namespace man::dataset::sensors {

namespace {
}

SensorBase::SensorBase(const Token& token, const std::string& channel, const Modality modality)
  : TOKEN_(token), CHANNEL_(channel), MODALITY_(modality)
{}

SensorBase::SensorBase(const Token& token, const std::string& channel, const std::string_view modality)
  : TOKEN_(token), CHANNEL_(channel), MODALITY_(string_to_modality(modality))
{}

SensorBase::SensorBase(const std::string& token, const std::string& channel, const std::string_view modality)
  : SensorBase(Token(token), channel, modality)
{}

std::ostream& operator<<(std::ostream& os, const SensorBase& sensor)
{
  os << "Sensor:\n\tToken: " << sensor.TOKEN_ 
     << "\n\tChannel: " << sensor.CHANNEL_ 
     << "\n\tModality: " << sensor.MODALITY_;
  return os;
}

}