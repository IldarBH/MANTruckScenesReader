#pragma once
#include "MANTruckDataset/utils.hpp"

#include <string>
#include <string_view>
#include <cstddef>
#include <unordered_map>

namespace man::dataset::scenes {

class Scene {
public:
  Scene(
    const std::string& name, 
    const std::string& description, 
    const std::string& token, 
    const std::string& first_sample_token, 
    const std::string& last_sample_token)
  : NAME_(name)
  , DESCRIPTION_(description)
  , TOKEN_(token)
  , FIRST_SAMPLE_TOKEN_(first_sample_token)
  , LAST_SAMPLE_TOKEN_(last_sample_token) 
  {}

  const std::string& get_name() const { return NAME_; }
  const std::string& get_description() const { return DESCRIPTION_; }
  const std::string& get_token() const { return TOKEN_; }
  const std::string& get_first_sample_token() const { return FIRST_SAMPLE_TOKEN_; }
  const std::string& get_last_sample_token() const { return LAST_SAMPLE_TOKEN_; }

  friend std::ostream& operator<<(std::ostream& os, const Scene& scene);
private:
  const std::string NAME_;
  const std::string DESCRIPTION_;
  const std::string TOKEN_;
  const std::string FIRST_SAMPLE_TOKEN_;
  const std::string LAST_SAMPLE_TOKEN_;
private:
};

inline std::ostream& operator<<(std::ostream& os, const Scene& scene) {
  os << "Scene:\n"
     << "\tToken: " << scene.TOKEN_ << "\n"
     << "\tName: " << scene.NAME_ << "\n"
     << "\tDescription: " << scene.DESCRIPTION_;
  return os;
}

namespace {
constexpr std::string_view SCENE_FIELD_NAME = "name";
constexpr std::string_view SCENE_FIELD_DESCRIPTION = "description";
constexpr std::string_view SCENE_FIELD_TOKEN = "token";
constexpr std::string_view SCENE_FIELD_FIRST_SAMPLE_TOKEN = "first_sample_token";
constexpr std::string_view SCENE_FIELD_LAST_SAMPLE_TOKEN = "last_sample_token";
}

class SceneManager {
public:
  SceneManager() = default;

  void read_scenes(const std::string& filename)
  {
    const auto data = read_json_file(filename);
    scenes_.reserve(data.size());
    for (const auto& item : data){
      this->add_scene(
        item.at(SCENE_FIELD_NAME).get<std::string>(), 
        item.at(SCENE_FIELD_DESCRIPTION).get<std::string>(), 
        item.at(SCENE_FIELD_TOKEN).get<std::string>(), 
        item.at(SCENE_FIELD_FIRST_SAMPLE_TOKEN).get<std::string>(),
        item.at(SCENE_FIELD_LAST_SAMPLE_TOKEN).get<std::string>()
      );
    }
  }

  void add_scene(const std::string& name,
                 const std::string& description,
                 const std::string& token,
                 const std::string& first_sample_token,
                 const std::string& last_sample_token)
  {
    scenes_.emplace(token, Scene(name, description, token, first_sample_token, last_sample_token));
  }

  const Scene& operator[](const std::string& token) const { return scenes_.at(token); }

  auto begin() const { return scenes_.begin(); }
  auto end() const { return scenes_.end(); }
  auto size() const { return scenes_.size(); }

private:
  std::unordered_map<std::string, Scene> scenes_;
};
}