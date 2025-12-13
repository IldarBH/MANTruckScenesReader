#include "utils.hpp"

#include <MANTruckDataset/Scene.hpp>

#include <string>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;
namespace man_ds = man::dataset;

int main(int argc, char** argv){
  if (argc < 2){
    std::cout << "Usage: './example <dataset_path>'";
    return -1;
  }
  const fs::path dataset_path(argv[1]);
  const std::string scene_file(dataset_path / "v1.0-mini" / "scene.json");
  
  man_ds::scenes::SceneManager scene_manager;
  scene_manager.read_scenes(scene_file);
  const auto& scene = select_scene(scene_manager);
  std::cout << scene << std::endl;
  return 0;
}