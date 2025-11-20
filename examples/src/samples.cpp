#include <MANTruckDataset/SamplesManager.hpp>
#include <pcl/visualization/pcl_visualizer.h>

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
  const std::string samples_file(dataset_path / "v1.0-mini" / "sample_data.json");
  
  man_ds::samples::SampleManager sm;
  sm.read_samples(samples_file);
  for (const auto& sample : sm){
    std::cout << *sample << std::endl;
  }
  return 0;
}