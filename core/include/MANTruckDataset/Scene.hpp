#pragma once
#include "MANTruckDataset/utils.hpp"

#include <string>
#include <cstddef>
#include <vector>

namespace man::dataset::scenes {

class Scene {
public:
  Scene(const std::string& name, const std::string& description, const std::string& token)
  : NAME(std::move(name))
  , DESCRIPTION(std::move(description))
  , TOKEN(std::move(token))
  {

  }
public:
  const std::string NAME;
  const std::string DESCRIPTION;
  const std::string TOKEN;
private:
};

inline std::ostream& operator<<(std::ostream& os, const Scene& scene) {
  os << "Scene:\n"
     << "\tToken: " << scene.TOKEN << "\n"
     << "\tName: " << scene.NAME << "\n"
     << "\tDescription: " << scene.DESCRIPTION;
  return os;
}

class SceneManager {
public:
  SceneManager() = default;

  void read_scenes(const std::string& filename){
    const auto data = read_json_file(filename);
    scenes_.reserve(data.size());
    for (const auto& item : data){
      scenes_.emplace_back(item.at("name").get<std::string>(), item.at("description").get<std::string>(), item.at("token").get<std::string>());
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