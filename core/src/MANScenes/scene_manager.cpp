#include "MANScenes/scene_manager.hpp"

#include <string_view>

namespace man::dataset::scenes {

namespace {
  constexpr std::string_view SCENE_FIELD_NAME = "name";
  constexpr std::string_view SCENE_FIELD_DESCRIPTION = "description";
  constexpr std::string_view SCENE_FIELD_TOKEN = "token";
  constexpr std::string_view SCENE_FIELD_FIRST_SAMPLE_TOKEN = "first_sample_token";
  constexpr std::string_view SCENE_FIELD_LAST_SAMPLE_TOKEN = "last_sample_token";
}

size_t SceneManager::read_scenes(const std::string& filename)
{
  scenes_.clear();
  const auto data = read_json_file(filename);
  scenes_.reserve(data.size());
  for (const auto& item : data){
    const Token token(item.at(SCENE_FIELD_TOKEN).get<std::string>());
    const auto name = item.at(SCENE_FIELD_NAME).get<std::string>();
    const auto description = item.at(SCENE_FIELD_DESCRIPTION).get<std::string>();
    auto scene = std::make_shared<Scene>(token, name, description);
    if (scenes_.find(scene) == scenes_.end()) {
      scenes_.emplace(scene);
    }
  }
  return scenes_.size();
}

}