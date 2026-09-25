#include "MANTruckDataset/utils.hpp"
#include "MANSamples/sample_manager.hpp"

#include <gtest/gtest.h>
#include <string_view>
#include <string>

namespace mands = man::dataset;

#ifndef TEST_DATA_DIR
#define TEST_DATA_DIR "data"
#endif

namespace {
  constexpr std::string_view TEST_SAMPLE_JSON = "sample.json";
  constexpr size_t TEST_JSON_SAMPLES_COUNT = 400;

  constexpr std::string_view TEST_DATA_JSON = "sample_data.json";
  constexpr size_t TEST_JSON_DATA_ITEMS_COUNT = 43556;
}

TEST(Sample, ReadSamples) {
  mands::samples::SampleManager sampleManager;
  const std::string test_file = std::string(TEST_DATA_DIR) + "/" + std::string(TEST_SAMPLE_JSON);
  ASSERT_EQ(sampleManager.read_samples(test_file), TEST_JSON_SAMPLES_COUNT);
}

TEST(DataItem, ReadDataItems) {
  mands::samples::SampleManager sampleManager;
  const std::string test_file = std::string(TEST_DATA_DIR) + "/" + std::string(TEST_DATA_JSON);
  ASSERT_EQ(sampleManager.read_samples_data(test_file), TEST_JSON_DATA_ITEMS_COUNT);
}