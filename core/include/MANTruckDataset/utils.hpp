#pragma once
#include <nlohmann/json.hpp>

#include <ostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <functional>

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
  std::string value = "";
  Token() = default;
  explicit Token(const char* v): value(v) {}
  explicit Token(const std::string& v) : value(v) {}
  explicit Token(const std::string_view v) : value(v) {}
  
  bool operator==(const Token& other) const {
    return value == other.value;
  }
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

inline std::ostream& operator<<(std::ostream& os, const Token& token) {
  os << token.value;
  return os;
};

}

namespace std {
  template<>
  struct hash<man::dataset::Token> {
    size_t operator()(const man::dataset::Token& t) const {
      return std::hash<std::string>{}(t.value);
    }
  };
}
