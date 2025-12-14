#pragma once
#include <nlohmann/json.hpp>

#include <ostream>
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

struct Token {
  std::string value;
  explicit Token(const std::string& v) : value(v) {}
  explicit Token(std::string_view v) : value(v) {}
};

struct TokenHash {
  size_t operator()(const Token& t) const {
    return std::hash<std::string>{}(t.value);
  }
};

struct TokenEqual {
  bool operator()(const Token& a, const Token& b) const {
    return a.value == b.value;
  }
};

std::ostream& operator<<(std::ostream& os, const Token& token) {
  os << token.value;
  return os;
};

}
