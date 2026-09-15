#pragma once
#include "MANSensors/modality.hpp"
#include "MANTruckDataset/utils.hpp"

namespace man::dataset::sensors {

class SensorBase {
public:
  using SPtr = std::shared_ptr<SensorBase>;
  using WPtr = std::weak_ptr<SensorBase>;

  SensorBase(const Token& token, 
             const std::string& channel, 
             const Modality modality);

  SensorBase(const Token& token, 
             const std::string& channel, 
             const std::string_view modality);

  SensorBase(const std::string& token, 
             const std::string& channel, 
             const std::string_view modality);

  const auto& get_token() const noexcept { return TOKEN_; }
  const auto& get_channel() const noexcept { return CHANNEL_; }
  const auto& get_modality() const noexcept { return MODALITY_; }

  friend std::ostream& operator<<(std::ostream& os, const SensorBase& sensor);  
private:
  const Token TOKEN_;
  const Modality MODALITY_;
  const std::string CHANNEL_;
};

std::ostream& operator<<(std::ostream& os, const SensorBase& sensor);

} // namespace man::dataset::sensors