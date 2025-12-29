#pragma once
#include <MANTruckDataset/Scene.hpp>
#include <MANTruckDataset/Sample.hpp>
#include <MANTruckDataset/Sensor.hpp>

#include <iostream>

namespace man_ds = man::dataset;

inline const man_ds::scenes::Scene& select_scene(const man_ds::scenes::SceneManager& scene_manager)
{
  std::cout << "Select scene to load:" << std::endl;
  std::vector<man_ds::Token> scene_tokens;
  scene_tokens.reserve(scene_manager.size());
  for (const auto& [token, scene] : scene_manager){
    scene_tokens.emplace_back(token);
    std::cout << scene_tokens.size() << ". " << scene.get_name() << std::endl;
  }
  std::cout << "Enter selection (1-" << scene_tokens.size() << "): ";

  size_t selection = 0;
  while (selection < 1 || selection > scene_tokens.size()){
    std::cin >> selection;
    if (selection < 1 || selection > scene_tokens.size()){
      std::cerr << "Invalid selection! Try again." << std::endl;
    }
  }

  const auto& scene = scene_manager[scene_tokens[selection - 1]];
  std::cout << "You have selected scene: " << scene.get_name() << std::endl;
  return scene;
}

inline const man_ds::samples::Sample& select_sample(const man_ds::samples::SampleSequence& sequence)
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
  std::cout << "Select sensor:" << std::endl;
  std::vector<man_ds::Token> sensor_tokens;
  for (const auto& sensor_ptr : sensor_manager){
    sensor_tokens.push_back(sensor_ptr->get_token());
  }
  for (size_t id = 0; id < sensor_tokens.size(); ++id){
    const auto& token = sensor_tokens[id];
    const auto& sensor = sensor_manager[man_ds::Token(token)];
    std::cout << id+1 << ". " << sensor.get_channel() << ", files: " << sensor.size() << std::endl;
  }
  std::cout << "Enter selection (1-" << sensor_manager.size() << "): ";

  size_t selection = 0;
  while (selection < 1 || selection > sensor_manager.size()){
    std::cin >> selection;
    if (selection < 1 || selection > sensor_manager.size()){
      std::cerr << "Invalid selection! Try again." << std::endl;
    }
  }
  const auto& sensor = sensor_manager[man_ds::Token(sensor_tokens[selection - 1])];
  std::cout << "You have selected sensor: " << sensor.get_token() << std::endl;
  return sensor;
}