#pragma once
#include "MANTruckDataset/utils.hpp"
#include "MANScenes/scene.hpp"

#include <memory>
#include <string>
#include <unordered_set>

namespace man::dataset::scenes {

struct SceneHash {
  size_t operator()(const Scene::SPtr& scene) const noexcept {
    return std::hash<man::dataset::Token>()(scene->TOKEN);
  }
};

struct SceneEqual {
  bool operator()(const Scene::SPtr& lhs, const Scene::SPtr& rhs) const noexcept {
    return lhs->TOKEN == rhs->TOKEN;
  }
};

class SceneManager {
public:
  SceneManager() = default;

  /**
   * @brief Read scenes from a JSON file.
   * @param filename Path to the JSON file.
   * @return Number of scenes read.
   */
  size_t read_scenes(const std::string& filename);

  /**
   * @brief Get all scenes.
   */
  const auto& get_scenes() const noexcept { return scenes_; }
private:
  std::unordered_set<Scene::SPtr, SceneHash, SceneEqual> scenes_;
};
}