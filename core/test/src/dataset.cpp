#include "MANTruckDataset/utils.hpp"
#include "MANTruckDataset/MANTruckDataset.hpp"

#include <gtest/gtest.h>
#include <string_view>
#include <string>
#include <filesystem>

namespace mands = man::dataset;
namespace fs = std::filesystem;

#ifndef TEST_DATA_DIR
#define TEST_DATA_DIR "data"
#endif

namespace {
  constexpr std::string_view TEST_SCENE_JSON = "scene.json";
  constexpr std::string_view TEST_SAMPLE_JSON = "sample.json";
  constexpr std::string_view TEST_DATA_JSON = "sample_data.json";
}

TEST(Dataset, ReadDataset) {
  const auto test_path = fs::path(TEST_DATA_DIR).parent_path();
  const auto test_data_folder  = "data";
  mands::MANTruckDataset dataset(test_path.string(), test_data_folder);

  std::stringstream in_stream, out_stream;
  in_stream << "1\n";
  const auto scene = mands::select_scene(dataset, out_stream, in_stream);
}