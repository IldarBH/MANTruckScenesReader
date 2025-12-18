#pragma once
#include "MANTruckDataset/utils.hpp"

#include <string>
#include <unordered_map>

namespace man::dataset::scenes {

class Scene {
public:
  Scene(const std::string& name, 
        const std::string& description, 
        const Token& token, 
        const std::string& first_sample_token, 
        const std::string& last_sample_token);

  Scene(const std::string& name, 
        const std::string& description, 
        const std::string& token, 
        const std::string& first_sample_token, 
        const std::string& last_sample_token);

  const auto& get_token() const noexcept { return TOKEN_; }
  const std::string& get_name() const noexcept { return NAME_; }
  const std::string& get_description() const noexcept { return DESCRIPTION_; }
  const std::string& get_first_sample_token() const noexcept { return FIRST_SAMPLE_TOKEN_; }
  const std::string& get_last_sample_token() const noexcept { return LAST_SAMPLE_TOKEN_; }

  friend std::ostream& operator<<(std::ostream& os, const Scene& scene);
private:
  const std::string NAME_;
  const std::string DESCRIPTION_;
  const Token TOKEN_;
  const std::string FIRST_SAMPLE_TOKEN_;
  const std::string LAST_SAMPLE_TOKEN_;
private:
};

std::ostream& operator<<(std::ostream& os, const Scene& scene);

class SceneManager {
public:
  SceneManager() = default;

  void read_scenes(const std::string& filename);

  void add_scene(const std::string& name, 
                 const std::string& description, 
                 const std::string& token, 
                 const std::string& first_sample_token, 
                 const std::string& last_sample_token)
  {
    scenes_.emplace(Token(token), Scene(name, description, token, first_sample_token, last_sample_token));
  }

  void add_scene(const std::string& name, 
                 const std::string& description, 
                 const Token& token, 
                 const std::string& first_sample_token, 
                 const std::string& last_sample_token)
  {
    scenes_.emplace(token, Scene(name, description, token, first_sample_token, last_sample_token));
  }

  const Scene& operator[](const Token& token) const { return scenes_.at(token); }

  auto size() const noexcept { return scenes_.size(); }
  auto begin() const noexcept { return scenes_.begin(); }
  auto end() const noexcept { return scenes_.end(); }
  auto cbegin() const noexcept { return scenes_.cbegin(); }
  auto cend() const noexcept { return scenes_.cend(); }
private:
  std::unordered_map<Token, Scene> scenes_;
};
}