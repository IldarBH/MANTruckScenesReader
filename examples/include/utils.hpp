#pragma once
#include <MANTruckDataset/Scene.hpp>

#include <iostream>

namespace man_ds = man::dataset;

inline const man_ds::scenes::Scene& select_scene(const man_ds::scenes::SceneManager& scene_manager)
{
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
  std::cout << "You have selected scene: " << scene.NAME << std::endl;
  return scene;
}