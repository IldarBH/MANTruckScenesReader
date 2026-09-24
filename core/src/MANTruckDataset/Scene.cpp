#include "MANTruckDataset/Scene.hpp"

#include <string_view>

namespace man::dataset::scenes {

namespace {
  constexpr std::string_view SCENE_FIELD_NAME = "name";
  constexpr std::string_view SCENE_FIELD_DESCRIPTION = "description";
  constexpr std::string_view SCENE_FIELD_TOKEN = "token";
  constexpr std::string_view SCENE_FIELD_FIRST_SAMPLE_TOKEN = "first_sample_token";
  constexpr std::string_view SCENE_FIELD_LAST_SAMPLE_TOKEN = "last_sample_token";
}

Scene::Scene(const Token& token, const std::string& name, const std::string& description)
: NAME(name), DESCRIPTION(description), TOKEN(token)
{}

std::ostream& operator<<(std::ostream& os, const Scene& scene) 
{
  os << "Scene:\n\tToken: " << scene.TOKEN.value << "\n\tName: " << scene.NAME << "\n\tDescription: " << scene.DESCRIPTION;
  return os;
}

size_t SceneManager::read_scenes(const std::string& filename)
{
  scenes_.clear();
  scenes_map_.clear();
  const auto data = read_json_file(filename);
  scenes_.reserve(data.size());
  scenes_map_.reserve(data.size());
  for (const auto& item : data){
    const Token token(item.at(SCENE_FIELD_TOKEN).get<std::string>());
    if (scenes_map_.find(token) == scenes_map_.end()) {
      const auto name = item.at(SCENE_FIELD_NAME).get<std::string>();
      const auto description = item.at(SCENE_FIELD_DESCRIPTION).get<std::string>();
      // const auto first_sample_token = Token(item.at(SCENE_FIELD_FIRST_SAMPLE_TOKEN).get<std::string>());
      // const auto last_sample_token = Token(item.at(SCENE_FIELD_LAST_SAMPLE_TOKEN).get<std::string>());
      this->add_scene_(token, name, description);
    }
  }
  return scenes_.size();
}

void SceneManager::add_scene_(const Token& token, const std::string& name, const std::string& description)
{
  scenes_.emplace_back(std::make_shared<Scene>(token, name, description));
  scenes_map_.emplace(token, scenes_.back());
}

}