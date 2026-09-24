#pragma once
#include "MANTruckDataset/utils.hpp"

#include <memory>
#include <string>
#include <ostream>
#include <unordered_set>

namespace man::dataset::scenes {

class Sample; // Forward declaration

class Scene {
public:
  using UPtr = std::unique_ptr<Scene>;
  using SPtr = std::shared_ptr<Scene>;
  using WPtr = std::weak_ptr<Scene>;

  Scene() = delete;
  
  Scene(const Token& token, const std::string& name = "", const std::string& description = "")
  : NAME(name), DESCRIPTION(description), TOKEN(token)
  {}

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

inline std::ostream& operator<<(std::ostream& os, const Scene& scene)
{
  os << "Scene:\n\tToken: " << scene.TOKEN.value << "\n\tName: " << scene.NAME << "\n\tDescription: " << scene.DESCRIPTION;
  return os;
}

} // namespace man::dataset::scenes