#pragma once
#include "MANTruckDataset/utils.hpp"

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

namespace man::dataset::scenes {

class Scene {
public:
  using SPtr = std::shared_ptr<Scene>;

  Scene(const std::string& name, 
        const std::string& description, 
        const Token& token, 
        const Token& first_sample_token, 
        const Token& last_sample_token);

  Scene(const std::string& name, 
        const std::string& description, 
        const std::string& token, 
        const std::string& first_sample_token, 
        const std::string& last_sample_token);

  const auto& get_token() const noexcept { return TOKEN_; }
  const auto& get_name() const noexcept { return NAME_; }
  const auto& get_description() const noexcept { return DESCRIPTION_; }
  const auto& get_first_sample_token() const noexcept { return FIRST_SAMPLE_TOKEN_; }
  const auto& get_last_sample_token() const noexcept { return LAST_SAMPLE_TOKEN_; }

  friend std::ostream& operator<<(std::ostream& os, const Scene& scene);
private:
  const std::string NAME_;
  const std::string DESCRIPTION_;
  const Token TOKEN_;
  const Token FIRST_SAMPLE_TOKEN_;
  const Token LAST_SAMPLE_TOKEN_;
private:
};

std::ostream& operator<<(std::ostream& os, const Scene& scene);

class SceneManager {
public:
  SceneManager() = default;

  /**
   * @brief Read scenes from a JSON file.
   * @param filename Path to the JSON file.
   */
  void read_scenes(const std::string& filename);

  /**
   * @brief Add a scene.
   * Overload that takes string tokens.
   * @param name Name of the scene.
   * @param description Description of the scene.
   * @param token Token of the scene.
   * @param first_sample_token Token of the first sample in the scene.
   * @param last_sample_token Token of the last sample in the scene.
   */
  void add_scene(
    const std::string& name, 
    const std::string& description, 
    const std::string& token, 
    const std::string& first_sample_token, 
    const std::string& last_sample_token);

  /**
   * @brief Add a scene.
   * Overload that takes Token objects.
   * @param name Name of the scene.
   * @param description Description of the scene.
   * @param token Token of the scene.
   * @param first_sample_token Token of the first sample in the scene.
   * @param last_sample_token Token of the last sample in the scene.
   */
  void add_scene(
    const std::string& name, 
    const std::string& description, 
    const Token& token, 
    const Token& first_sample_token, 
    const Token& last_sample_token);
  
  /**
   * @brief Get all scenes.
   */
  const auto& get_scenes() const noexcept { return scenes_; }

  const auto& operator[](const size_t id) const { return scenes_[id]; }
  const auto& operator[](const Token& token) const { return scenes_map_.at(token); }
  auto begin() const noexcept { return scenes_map_.begin(); }
  auto end() const noexcept { return scenes_map_.end(); }
  auto cbegin() const noexcept { return scenes_map_.cbegin(); }
  auto cend() const noexcept { return scenes_map_.cend(); }
  auto size() const noexcept { return scenes_map_.size(); }
private:
  std::vector<Scene::SPtr> scenes_;
  std::unordered_map<Token, Scene::SPtr> scenes_map_;
};
}