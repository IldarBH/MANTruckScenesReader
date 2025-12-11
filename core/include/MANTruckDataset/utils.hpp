#pragma once
#include <nlohmann/json.hpp>

#include <string>
#include <fstream>

namespace man::dataset {

inline nlohmann::json read_json_file(const std::string& filepath) {
  std::ifstream file(filepath);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file: " + filepath);
  }
  nlohmann::json json;
  file >> json;
  return json;
}

}
