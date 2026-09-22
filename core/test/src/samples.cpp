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

  const mands::Token SAMPLE_TOKEN_1("sample_1");
  const mands::Token SAMPLE_TOKEN_2("sample_2");
  const mands::Token SAMPLE_TOKEN_3("sample_3");
  const mands::Token SCENE_TOKEN("some_scene_token");
  constexpr int64_t TIMESTAMP = 1234567890;
}


TEST(Sample, BasicConstructor) {
  mands::samples::Sample sample(SAMPLE_TOKEN_1, SCENE_TOKEN, TIMESTAMP);
  EXPECT_EQ(sample.get_token(), SAMPLE_TOKEN_1);
  EXPECT_EQ(sample.get_scene_token(), SCENE_TOKEN);
  EXPECT_EQ(sample.get_timestamp(), TIMESTAMP);
}


TEST(Sample, CopyConstructor) {
  mands::samples::Sample sample_1(SAMPLE_TOKEN_1, SCENE_TOKEN, TIMESTAMP);
  mands::samples::Sample sample_2(sample_1);
  EXPECT_EQ(sample_2.get_token(), SAMPLE_TOKEN_1);
  EXPECT_EQ(sample_2.get_scene_token(), SCENE_TOKEN);
  EXPECT_EQ(sample_2.get_timestamp(), TIMESTAMP);
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