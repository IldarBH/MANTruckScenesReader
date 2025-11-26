#include <MANTruckDataset/MANTruckDataset.hpp>

#include <filesystem>

namespace fs = std::filesystem;
namespace man_ds = man::dataset;

int main(int argc, char** argv){
  if (argc < 2){
    std::cout << "Usage: './example <dataset_path>'";
    return -1;
  }
  const fs::path dataset_path(std::string(argv[1]) + "/v1.0-mini");
  const std::string scene_token = "073e6bb18188424ea9981e3845df54a6"; // Example scene token
  man_ds::MANTruckDataset dataset(dataset_path.string(), scene_token, {});
  
  return 0;
}