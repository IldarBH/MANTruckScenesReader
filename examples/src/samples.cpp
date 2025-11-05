#include <iostream>
#include <MANTruckDataset/SamplesManager.hpp>

#include <string>
#include <filesystem>

namespace fs = std::filesystem;
namespace man_ds = man::dataset::samples;

int main(int argc, char** argv){
  if (argc < 2){
    std::cout << "Usage: './example <dataset_path>'";
    return -1;
  }
  const fs::path dataset_path(argv[1]);
  const std::string samples_file(dataset_path / "v1.0-mini" / "sample_data.json");
  
  man_ds::SampleManager sm;
  sm.read_samples(samples_file);
  const auto& sample = sm[0];
  man_ds::print_samples_chain(sample);
  return 0;
}