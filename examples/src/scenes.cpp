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
  const std::string samples_file(dataset_path / "v1.0-mini" / "scene.json");
  
  man_ds::scenes::SceneManager scene_manager;
  scene_manager.read_scenes(samples_file);
  std::cout << "Select scene to load:" << std::endl;
  for (size_t id = 0; id < scene_manager.size(); ++id){
    std::cout << id+1 << ". " << scene_manager[id].NAME << std::endl;
  }
  std::cout << "Enter selection (1-" << scene_manager.size() << "): ";

  size_t selection = 0;
  while (selection < 1 || selection > scene_manager.size()){
    std::cin >> selection;
    if (selection < 1 || selection > scene_manager.size()){
      std::cerr << "Invalid selection! Try again." << std::endl;
    }
  }
  
  const auto& scene = scene_manager[selection - 1];
  std::cout << "You have selected scene:" << std::endl;
  std::cout << scene << std::endl;
  return 0;
}