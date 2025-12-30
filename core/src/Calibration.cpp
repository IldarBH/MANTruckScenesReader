#include <MANTruckDataset/Calibration.hpp>

#include <string_view>

namespace man::dataset::calibration {

namespace {
    constexpr std::string_view TOKEN_KEY = "token";
    constexpr std::string_view SENSOR_TOKEN_KEY = "sensor_token";
}

Calibration::Calibration(const Token& token, const Token& sensor_token, 
  const std::vector<double>& translation, const std::vector<double>& rotation)
: TOKEN_(token)
, SENSOR_TOKEN_(sensor_token)
, TRANSLATION_(Eigen::Vector3d(translation.data()))
, ROTATION_(Eigen::Quaterniond(rotation.data()))
{}

std::ostream& operator<<(std::ostream& os, const Calibration& calib)
{
  os << "Calibration:\n"
     << "\tToken: " << calib.get_token() << "\n"
     << "\tSensor Token: " << calib.get_sensor_token() << "\n"
     << "\tTranslation: " << calib.get_translation().transpose() << "\n"
     << "\tRotation (x,y,z,w): " << calib.get_rotation().coeffs().transpose();
  return os;
}

void CalibrationManager::read_calibrations(const std::string& filename, const std::vector<Token>& sensor_tokens)
{
  std::unordered_set<Token> filter_set(sensor_tokens.begin(), sensor_tokens.end());
  const auto json_file = read_json_file(filename);
  this->parse_json_(json_file, filter_set);
}

void CalibrationManager::add_calibration(const Token& token, const Token& sensor_token, const std::vector<double>& translation, const std::vector<double>& rotation)
{
  const auto iter = calibrations_.emplace(
    std::make_pair(token, Calibration(token, sensor_token, translation, rotation)));
  #ifdef DEBUG_BUILD
    std::cout << iter.first->second << std::endl;
  #endif
}

void CalibrationManager::parse_json_(const nlohmann::json& data, const std::unordered_set<Token>& filter_tokens)
{
  for (const auto& item : data) {
    const Token sensor_token(item.at(SENSOR_TOKEN_KEY).get<std::string>());
    if (!filter_tokens.empty() && (filter_tokens.find(sensor_token) == filter_tokens.end())) {
      continue;
    }
    add_calibration(
      Token(item.at(TOKEN_KEY).get<std::string>()), 
      sensor_token, 
      item["translation"].get<std::vector<double>>(), 
      item["rotation"].get<std::vector<double>>()
    );
  }
}

bool CalibrationManager::token_exists(const Token& token) const noexcept 
{ 
  return calibrations_.find(token) != calibrations_.end(); 
}

const Calibration& CalibrationManager::operator[](const Token& token) const
{
  const auto iter = calibrations_.find(token);
  if (iter == calibrations_.end()) {
    throw std::runtime_error("Calibration with token " + token.value + " not found.");
  }
  return iter->second;
}

}