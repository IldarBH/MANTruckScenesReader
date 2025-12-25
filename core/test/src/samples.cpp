#include "MANTruckDataset/utils.hpp"
#include "MANTruckDataset/Sample.hpp"

#include <gtest/gtest.h>
#include <string_view>
#include <string>

namespace man_ds = man::dataset;

namespace {
  const man_ds::Token SAMPLE_TOKEN_1("sample_1");
  const man_ds::Token SAMPLE_TOKEN_2("sample_2");
  const man_ds::Token SAMPLE_TOKEN_3("sample_3");
  const man_ds::Token SCENE_TOKEN("some_scene_token");
  constexpr int64_t TIMESTAMP = 1234567890;
}


TEST(SampleTest, BasicConstructor) {
  man_ds::samples::Sample sample(SAMPLE_TOKEN_1, SCENE_TOKEN, TIMESTAMP);
  EXPECT_EQ(sample.get_token(), SAMPLE_TOKEN_1);
  EXPECT_EQ(sample.get_scene_token(), SCENE_TOKEN);
  EXPECT_EQ(sample.get_timestamp(), TIMESTAMP);
}


TEST(SampleTest, CopyConstructor) {
  man_ds::samples::Sample sample_1(SAMPLE_TOKEN_1, SCENE_TOKEN, TIMESTAMP);
  man_ds::samples::Sample sample_2(sample_1);
  EXPECT_EQ(sample_2.get_token(), SAMPLE_TOKEN_1);
  EXPECT_EQ(sample_2.get_scene_token(), SCENE_TOKEN);
  EXPECT_EQ(sample_2.get_timestamp(), TIMESTAMP);
}

TEST(SampleTest, BasicDestructor) {
  const auto help_validate_sequence = [](
      const man_ds::samples::Sample* start_sample, 
      const std::initializer_list<man_ds::Token>& tokens) 
  {
    auto sample = start_sample;
    for (const auto& token : tokens) {
      EXPECT_EQ(sample->get_token(), token);
      sample = sample->get_next_sample();
    }
  };
  const auto sample_1 = std::make_shared<man_ds::samples::Sample>(SAMPLE_TOKEN_1, SCENE_TOKEN, 0);
  {
    const auto sample_2 = std::make_shared<man_ds::samples::Sample>(SAMPLE_TOKEN_2, SCENE_TOKEN, 2, sample_1.get());
    {
      const auto sample_3 = std::make_shared<man_ds::samples::Sample>(SAMPLE_TOKEN_3, SCENE_TOKEN, 1, sample_1.get(), sample_2.get());
      help_validate_sequence(sample_1.get(), {SAMPLE_TOKEN_1, SAMPLE_TOKEN_3, SAMPLE_TOKEN_2});
    }
    help_validate_sequence(sample_1.get(), {SAMPLE_TOKEN_1, SAMPLE_TOKEN_2});
  }
  help_validate_sequence(sample_1.get(), {SAMPLE_TOKEN_1});
}