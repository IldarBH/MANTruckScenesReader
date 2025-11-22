#include "MANTruckDataset/Sample.hpp"

#include <gtest/gtest.h>
#include <string_view>

namespace man_ds = man::dataset;

namespace {
constexpr std::string_view SAMPLE_TOKEN = "some_token";
constexpr std::string_view SCENE_TOKEN = "some_scene_token";
constexpr int64_t TIMESTAMP = 1234567890;
}


TEST(SampleTest, BasicConstructor) {
  man_ds::samples::Sample sample(SAMPLE_TOKEN.data(), SCENE_TOKEN.data(), TIMESTAMP);
  EXPECT_EQ(sample.get_token(), SAMPLE_TOKEN);
  EXPECT_EQ(sample.get_scene_token(), SCENE_TOKEN);
  EXPECT_EQ(sample.get_timestamp(), TIMESTAMP);
}


TEST(SampleTest, CopyConstructor) {
  man_ds::samples::Sample sample_1(SAMPLE_TOKEN.data(), SCENE_TOKEN.data(), TIMESTAMP);
  man_ds::samples::Sample sample_2(sample_1);
  EXPECT_EQ(sample_2.get_token(), SAMPLE_TOKEN);
  EXPECT_EQ(sample_2.get_scene_token(), SCENE_TOKEN);
  EXPECT_EQ(sample_2.get_timestamp(), TIMESTAMP);
}

TEST(SampleTest, BasicDestructor) {
  const auto help_validate_sequence = [](
    const man_ds::samples::Sample* start_sample, const std::initializer_list<std::string>& tokens) 
  {
    auto sample = start_sample;
    for (const auto& token : tokens) {
      EXPECT_EQ(sample->get_token(), token);
      sample = sample->get_next_sample();
    }
  };
  const auto sample_1 = std::make_shared<man_ds::samples::Sample>("sample_1", SCENE_TOKEN.data(), 0);
  {
    const auto sample_2 = std::make_shared<man_ds::samples::Sample>("sample_2", SCENE_TOKEN.data(), 2, sample_1.get());
    {
      const auto sample_3 = std::make_shared<man_ds::samples::Sample>("sample_3", SCENE_TOKEN.data(), 1, sample_1.get(), sample_2.get());
      help_validate_sequence(sample_1.get(), {"sample_1", "sample_3", "sample_2"});
    }
    help_validate_sequence(sample_1.get(), {"sample_1", "sample_2"});
  }
  help_validate_sequence(sample_1.get(), {"sample_1"});
}