#pragma once
#include "MANTruckDataset/utils.hpp"

#include <memory>
#include <string>
#include <ostream>
#include <functional>
#include <unordered_set>

namespace man::dataset::samples {
  // Forward declarations
  class Sample; 
  class SampleManager;
}

namespace man::dataset::scenes {

class Scene {
public:
  using UPtr = std::unique_ptr<Scene>;
  using SPtr = std::shared_ptr<Scene>;
  using WPtr = std::weak_ptr<Scene>;

  Scene() = delete;
  
  Scene(const Token& token, 
        const std::string& name = "", 
        const std::string& description = "")
  : NAME(name), DESCRIPTION(description), TOKEN(token)
  {}

  std::shared_ptr<samples::Sample> get_first_sample() const { return first_sample_.lock(); }
  std::shared_ptr<samples::Sample> get_last_sample() const { return last_sample_.lock(); }
  void set_first_sample(const std::shared_ptr<samples::Sample>& sample) { first_sample_ = sample; }
  void set_last_sample(const std::shared_ptr<samples::Sample>& sample) { last_sample_ = sample; }

  const Token TOKEN;
  const std::string NAME;
  const std::string DESCRIPTION;
private:
  std::weak_ptr<samples::Sample> first_sample_;
  std::weak_ptr<samples::Sample> last_sample_;
};

struct SceneHash {
  using is_transparent = void; // Required for C++20 heterogeneous lookup

  size_t operator()(const Scene::SPtr& scene) const noexcept {
    return std::hash<man::dataset::Token>()(scene->TOKEN);
  }

  size_t operator()(const Token& token) const noexcept {
    return std::hash<man::dataset::Token>()(token);
  }
};

struct SceneEqual {
  using is_transparent = void; // Required for C++20 heterogeneous lookup

  bool operator()(const Scene::SPtr& lhs, const Scene::SPtr& rhs) const noexcept {
    return lhs->TOKEN == rhs->TOKEN;
  }

  bool operator()(const Scene::SPtr& lhs, const Token& rhs) const noexcept {
    return lhs->TOKEN == rhs;
  }

  bool operator()(const Token& lhs, const Scene::SPtr& rhs) const noexcept {
    return lhs == rhs->TOKEN;
  }
};

using SceneSet = std::unordered_set<Scene::SPtr, SceneHash, SceneEqual>;

inline std::ostream& operator<<(std::ostream& os, const Scene& scene)
{
  os << "Scene:\n\tToken: " << scene.TOKEN.value << "\n\tName: " << scene.NAME << "\n\tDescription: " << scene.DESCRIPTION;
  return os;
}

} // namespace man::dataset::scenes