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

Scene::Scene(
  const std::string& name, 
  const std::string& description, 
  const Token& token, 
  const Token& first_sample_token, 
  const Token& last_sample_token)
: NAME_(name)
, DESCRIPTION_(description)
, TOKEN_(token)
, FIRST_SAMPLE_TOKEN_(first_sample_token)
, LAST_SAMPLE_TOKEN_(last_sample_token) 
{}

Scene::Scene(
  const std::string& name, 
  const std::string& description, 
  const std::string& token, 
  const std::string& first_sample_token, 
  const std::string& last_sample_token)
  : Scene(name, description, Token(token), Token(first_sample_token), Token(last_sample_token)) 
{}

std::ostream& operator<<(std::ostream& os, const Scene& scene) 
{
  os << "Scene:\n\tToken: " << scene.TOKEN_.value << "\n\tName: " << scene.NAME_ << "\n\tDescription: " << scene.DESCRIPTION_;
  return os;
}

void SceneManager::read_scenes(const std::string& filename)
{
  const auto data = read_json_file(filename);
  scenes_.reserve(data.size());
  for (const auto& item : data){
    const Token token(item.at(SCENE_FIELD_TOKEN).get<std::string>());
    if (scenes_.find(token) == scenes_.end()) {
      const auto first_sample_token = Token(item.at(SCENE_FIELD_FIRST_SAMPLE_TOKEN).get<std::string>());
      const auto last_sample_token = Token(item.at(SCENE_FIELD_LAST_SAMPLE_TOKEN).get<std::string>());
      this->add_scene(
        item.at(SCENE_FIELD_NAME).get<std::string>(), item.at(SCENE_FIELD_DESCRIPTION).get<std::string>(),
        token, first_sample_token, last_sample_token
      );
    }
    
  }
}

void SceneManager::add_scene(
  const std::string& name, 
  const std::string& description, 
  const std::string& token, 
  const std::string& first_sample_token, 
  const std::string& last_sample_token)
{
  scenes_.emplace(Token(token), Scene(name, description, token, first_sample_token, last_sample_token));
}

void SceneManager::add_scene(
  const std::string& name, 
  const std::string& description, 
  const Token& token, 
  const Token& first_sample_token, 
  const Token& last_sample_token)
{
  scenes_.emplace(token, Scene(name, description, token, first_sample_token, last_sample_token));
}

}