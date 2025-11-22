#include "utils.hpp"
#include <MANTruckDataset/Scene.hpp>
#include <MANTruckDataset/Sample.hpp>
#include <MANTruckDataset/DataSample.hpp>

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

  const std::string sample_file(dataset_path / "v1.0-mini" / "sample.json");
  man_ds::samples::SampleSequence sample_sequence;
  sample_sequence.read_samples(sample_file, scene.TOKEN);
  std::cout << "Number of samples in scene: " << sample_sequence.size() << std::endl;

  const std::string data_sample_file(dataset_path / "v1.0-mini" / "sample_data.json");
  man_ds::data_samples::DataSequence data_sequence;
  for (const auto& sample_ptr : sample_sequence){
    std::cout << "Reading samples from: " << sample_ptr->get_token() << ". ";
    data_sequence.read_samples(data_sample_file, sample_ptr->get_token());
    std::cout << "Total data samples read: " << data_sequence.size() << std::endl;
  }
  
  if (!data_sequence.is_complete()){
    std::cerr << "Warning: Data sequence is incomplete." << std::endl;
  }
  std::cout << "Number of data samples for selected sample: " << data_sequence.size() << std::endl;
  return 0;
}