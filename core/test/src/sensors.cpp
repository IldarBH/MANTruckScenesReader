#include <MANTruckDataset/utils.hpp>
#include <MANTruckDataset/Sensor.hpp>

#include <gtest/gtest.h>

#include <array>
#include <filesystem>
#include <string_view>

#ifndef TEST_DATA_DIR
#define TEST_DATA_DIR "data"
#endif

namespace mands = man::dataset;

namespace{
  constexpr std::string_view TEST_SENSORS_JSON = "sensor.json";
  const std::array<mands::Token, 18> TEST_SENSORS_TOKENS = {
    mands::Token("b3dd3279d239492195f64963ec70b244"),
    mands::Token("c7b216f6c0c2426ea01e20ffb50ecfb0"),
    mands::Token("27587edfa74844ce931a710995531ca9"),
    mands::Token("fb5519c659a5400c8e9bbf6ec2e50528"),
    mands::Token("0785ec5f7a5e4c93a99fea2ad781783d"),
    mands::Token("e70adcb9ee16435abc316cfd73c58fd7"),
    mands::Token("1c4f2bbb64f847a193c748c1c14f0574"),
    mands::Token("fe19aa64da874708a8cd417103e7cdc7"),
    mands::Token("3f53edcde9e44caaba5e689726c7aab7"),
    mands::Token("9ecd75e3eaf643d5b1d5a6cefba7f1f3"),
    mands::Token("fcddf720b15b4bc3b59eef0bdf3e0f94"),
    mands::Token("40dad62928a4498699eebf9aa7f4be98"),
    mands::Token("0a129b96d3a3483eb63a507f0452ac58"),
    mands::Token("ac1ee5f8d2b94fe2bb1206a0e8f44dfa"),
    mands::Token("34b35c4e51844611bf27f578cad4fbc9"),
    mands::Token("526e1b4441ea49bda0c3ee6bdbd085cd"),
    mands::Token("9f4db3741c2a45979e94196c93e5a331"),
    mands::Token("84cf08668ff84bbd883eaea4e5bd074f")
  };
}

TEST(Sensors, LoadFromJson) {
  const std::string testDataDir = std::string(TEST_DATA_DIR) + "/" + std::string(TEST_SENSORS_JSON);
  mands::sensors::SensorManager sensorManager;
  ASSERT_TRUE(sensorManager.read_sensors(testDataDir));
  ASSERT_EQ(sensorManager.size(), TEST_SENSORS_TOKENS.size());
  for (size_t i = 0; i < sensorManager.size(); ++i) {
    const auto& sensor = sensorManager[i];
    ASSERT_EQ(sensor.get_token(), TEST_SENSORS_TOKENS[i]);
  }
}
