#include "MANTruckDataset/utils.hpp"
#include "MANTruckDataset/Sample.hpp"

#include <gtest/gtest.h>
#include <string_view>
#include <string>

namespace mands = man::dataset;

#ifndef TEST_DATA_DIR
#define TEST_DATA_DIR "data"
#endif

namespace {
  constexpr std::string_view TEST_JSON = "sample.json";
  constexpr size_t TEST_JSON_SAMPLES_COUNT = 400;

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

TEST(Sample, BasicDestructor) {
  const auto help_validate_sequence = [](
      const mands::samples::Sample* start_sample, 
      const std::initializer_list<mands::Token>& tokens) 
  {
    auto sample = start_sample;
    for (const auto& token : tokens) {
      EXPECT_EQ(sample->get_token(), token);
      sample = sample->get_next_sample();
    }
  };
  const auto sample_1 = std::make_shared<mands::samples::Sample>(SAMPLE_TOKEN_1, SCENE_TOKEN, 0);
  {
    const auto sample_2 = std::make_shared<mands::samples::Sample>(SAMPLE_TOKEN_2, SCENE_TOKEN, 2, sample_1.get());
    {
      const auto sample_3 = std::make_shared<mands::samples::Sample>(SAMPLE_TOKEN_3, SCENE_TOKEN, 1, sample_1.get(), sample_2.get());
      help_validate_sequence(sample_1.get(), {SAMPLE_TOKEN_1, SAMPLE_TOKEN_3, SAMPLE_TOKEN_2});
    }
    help_validate_sequence(sample_1.get(), {SAMPLE_TOKEN_1, SAMPLE_TOKEN_2});
  }
  help_validate_sequence(sample_1.get(), {SAMPLE_TOKEN_1});
}

TEST(Sample, LoadFromJson) {
  const std::string test_file = std::string(TEST_DATA_DIR) + "/" + std::string(TEST_JSON);
  mands::samples::SampleManager sampleManager;
  ASSERT_EQ(sampleManager.read_samples(test_file), TEST_JSON_SAMPLES_COUNT);
  // TODO: add more tests to validate the loaded samples
}