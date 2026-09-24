#pragma once
#include "MANTruckDataset/utils.hpp"

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

namespace man::dataset::scenes {

class Sample; // Forward declaration

class Scene {
public:
  using UPtr = std::unique_ptr<Scene>;
  using SPtr = std::shared_ptr<Scene>;
  using WPtr = std::weak_ptr<Scene>;

  Scene(const Token& token,
        const std::string& name, 
        const std::string& description);

  const auto& get_token() const noexcept { return TOKEN; }
  const auto& get_name() const noexcept { return NAME; }
  const auto& get_description() const noexcept { return DESCRIPTION; }
  std::shared_ptr<Sample> get_first_sample() const { return first_sample_.lock(); }
  std::shared_ptr<Sample> get_last_sample() const { return last_sample_.lock(); }
  void set_first_sample(const std::shared_ptr<Sample>& sample) { first_sample_ = sample; }
  void set_last_sample(const std::shared_ptr<Sample>& sample) { last_sample_ = sample; }

  const Token TOKEN;
  const std::string NAME;
  const std::string DESCRIPTION;
private:
  std::weak_ptr<Sample> first_sample_;
  std::weak_ptr<Sample> last_sample_;
};

std::ostream& operator<<(std::ostream& os, const Scene& scene);

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
  /**
   * @brief Add a scene.
   * Overload that takes Token objects.
   * @param token Token of the scene.
   * @param name Name of the scene.
   * @param description Description of the scene.
   */
  void add_scene_(const Token& token, const std::string& name, const std::string& description);

  std::vector<Scene::SPtr> scenes_;
  std::unordered_map<Token, Scene::SPtr> scenes_map_;
};
}