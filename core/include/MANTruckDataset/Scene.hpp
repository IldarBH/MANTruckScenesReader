#pragma once
#include "MANTruckDataset/utils.hpp"

#include <string>
#include <string_view>
#include <cstddef>
#include <vector>

namespace man::dataset::scenes {

class Scene {
public:
  Scene(
    const std::string& name, 
    const std::string& description, 
    const std::string& token, 
    const std::string& first_sample_token, 
    const std::string& last_sample_token)
  : NAME(name)
  , DESCRIPTION(description)
  , TOKEN(token)
  , FIRST_SAMPLE_TOKEN(first_sample_token)
  , LAST_SAMPLE_TOKEN(last_sample_token) 
  {}

public:
  const std::string NAME;
  const std::string DESCRIPTION;
  const std::string TOKEN;
  const std::string FIRST_SAMPLE_TOKEN;
  const std::string LAST_SAMPLE_TOKEN;
private:
};

inline std::ostream& operator<<(std::ostream& os, const Scene& scene) {
  os << "Scene:\n"
     << "\tToken: " << scene.TOKEN << "\n"
     << "\tName: " << scene.NAME << "\n"
     << "\tDescription: " << scene.DESCRIPTION;
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

  void read_scenes(const std::string& filename){
    const auto data = read_json_file(filename);
    scenes_.reserve(data.size());
    for (const auto& item : data){
      scenes_.emplace_back(
        item.at(SCENE_FIELD_NAME).get<std::string>(), 
        item.at(SCENE_FIELD_DESCRIPTION).get<std::string>(), 
        item.at(SCENE_FIELD_TOKEN).get<std::string>(), 
        item.at(SCENE_FIELD_FIRST_SAMPLE_TOKEN).get<std::string>(),
        item.at(SCENE_FIELD_LAST_SAMPLE_TOKEN).get<std::string>()
      );
    }
  }

  void add_scene(const Scene& scene){
    scenes_.emplace_back(scene);
  }

  std::size_t size() const {
    return scenes_.size();
  }

  const Scene& operator[](std::size_t index) const {
    return scenes_[index];
  }

  auto begin() const {
    return scenes_.begin();
  }

  auto end() const {
    return scenes_.end();
  }
private:
  std::vector<Scene> scenes_;
};
}