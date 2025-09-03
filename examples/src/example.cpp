#include <iostream>
#include <MANTruckDataset/MANTruckDataset.hpp>

int main(int argc, char** argv){
  if (argc < 2){
    std::cout << "Usage: './example <dataset_path>'";
    return -1;
  }
  const std::string dataset_path = argv[1];
  MANTruckDataset man_dataset(dataset_path);
  return 0;
}