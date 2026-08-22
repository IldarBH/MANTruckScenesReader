#pragma once
#include <MANTruckDataset/Scene.hpp>
#include <MANTruckDataset/Sample.hpp>
#include <MANTruckDataset/Sensor.hpp>

#include <iostream>

namespace man_ds = man::dataset;

inline auto& select_scene(const man_ds::scenes::SceneManager& scene_manager)
{
  std::cout << "Select scene to load:" << std::endl;
  for (size_t id = 0; id < scene_manager.size(); ++id){
    std::cout << id + 1 << ". " << *scene_manager[id] << std::endl;
  }
  std::cout << "Enter selection (1-" << scene_manager.size() << "): ";

  size_t selection = 0;
  while (selection < 1 || selection > scene_manager.size()){
    std::cin >> selection;
    if (selection < 1 || selection > scene_manager.size()){
      std::cerr << "Invalid selection! Try again." << std::endl;
    }
  }
  return *scene_manager[selection - 1];
}

inline const man_ds::samples::Sample& select_sample(const man_ds::samples::SampleManager& sequence)
{
  std::cout << "Select sample to load:" << std::endl;
  for (size_t id = 0; id < sequence.size(); ++id){
    std::cout << id+1 << ". " << sequence[id].get_token() << std::endl;
  }
  std::cout << "Enter selection (1-" << sequence.size() << "): ";

  size_t selection = 0;
  while (selection < 1 || selection > sequence.size()){
    std::cin >> selection;
    if (selection < 1 || selection > sequence.size()){
      std::cerr << "Invalid selection! Try again." << std::endl;
    }
  }

  const auto& sample = sequence[selection - 1];
  std::cout << "You have selected scene: " << sample.get_token() << std::endl;
  return sample;
}


inline const man_ds::sensors::SensorBase& select_sensor(const man_ds::sensors::SensorManager& sensor_manager)
{
  std::cout << "Select sensor to load:" << std::endl;
  for (size_t id = 0; id < sensor_manager.size(); ++id){
    std::cout << id+1 << ". " << sensor_manager[id] << std::endl;
  }
  std::cout << "Enter selection (1-" << sensor_manager.size() << "): ";

  size_t selection = 0;
  while (selection < 1 || selection > sensor_manager.size()){
    std::cin >> selection;
    if (selection < 1 || selection > sensor_manager.size()){
      std::cerr << "Invalid selection! Try again." << std::endl;
    }
  }
  return sensor_manager[selection - 1];
}