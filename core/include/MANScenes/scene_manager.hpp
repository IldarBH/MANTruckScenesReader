#pragma once
#include "MANTruckDataset/utils.hpp"
#include "MANScenes/scene.hpp"

#include <memory>
#include <string>
#include <unordered_set>

namespace man::dataset::scenes {


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

  friend samples::SampleManager;
private:
  SceneSet scenes_;
};
}