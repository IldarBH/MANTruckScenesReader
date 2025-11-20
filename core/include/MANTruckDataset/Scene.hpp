#pragma once

#include <string>
#include <cstddef>

namespace man::dataset::samples {

class Scene {
public:
  Scene(const std::string& name, const std::string& description, const std::string& token)
  : NAME(std::move(name))
  , DESCRIPTION(std::move(description))
  , TOKEN(std::move(token))
  {

  }
public:
  const std::string NAME;
  const std::string DESCRIPTION;
  const std::string TOKEN;
private:
};

}