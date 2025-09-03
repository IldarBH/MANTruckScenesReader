#pragma once

#include <string>
#include <filesystem>

namespace fs = std::filesystem;

class MANTruckDataset {
public:
  explicit MANTruckDataset(const std::string& dataset_folder);

private:
  const fs::path DATASET_PATH_;
};