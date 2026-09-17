#include <MANTruckDataset/utils.hpp>
#include <MANSensors/modality.hpp>
#include <MANSensors/sensor_manager.hpp>

#include <gtest/gtest.h>

#include <array>
#include <string_view>

#ifndef TEST_DATA_DIR
#define TEST_DATA_DIR "data"
#endif

namespace mands = man::dataset;

namespace{
  constexpr std::string_view TEST_SENSOR_JSON = "sensor.json";
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

  struct CalibrationTestData {
    CalibrationTestData(const std::string& token, const std::string& sensor_token)
      : TOKEN(token), SENSOR_TOKEN(sensor_token) {}
    const std::string TOKEN;
    const std::string SENSOR_TOKEN;
  };

  constexpr std::string_view TEST_CALIBRATION_JSON = "calibrated_sensor.json";
  const std::array<CalibrationTestData, 18> TEST_CALIBRATION_TOKENS = {
    CalibrationTestData("f2c73d43e0994ee8a16f930860856c0e", "b3dd3279d239492195f64963ec70b244"),
    CalibrationTestData("8bef64c60da74778a5b9ef975c97edb7", "c7b216f6c0c2426ea01e20ffb50ecfb0"),
    CalibrationTestData("3126c35b164c459d85e0a0555ccba628", "27587edfa74844ce931a710995531ca9"),
    CalibrationTestData("5e6c5afaa842478db6066e9de8dec1ef", "fb5519c659a5400c8e9bbf6ec2e50528"),
    CalibrationTestData("cbecfab3ced24bbeab0a1b1bdd4375a8", "0785ec5f7a5e4c93a99fea2ad781783d"),
    CalibrationTestData("326989c743c948bf86229f525d0deb2d", "e70adcb9ee16435abc316cfd73c58fd7"),
    CalibrationTestData("2e6c7b7b7ceb4f69be01f9006cedf58f", "1c4f2bbb64f847a193c748c1c14f0574"),
    CalibrationTestData("aefabf5dd96744beb296b9881d60ff8b", "fe19aa64da874708a8cd417103e7cdc7"),
    CalibrationTestData("f994daad50a14ac49f1468d66eb8db62", "3f53edcde9e44caaba5e689726c7aab7"),
    CalibrationTestData("373fca46a765439794d1ecbb5839a161", "9ecd75e3eaf643d5b1d5a6cefba7f1f3"),
    CalibrationTestData("f8849496a35c4af599b8e598afda166d", "fcddf720b15b4bc3b59eef0bdf3e0f94"),
    CalibrationTestData("7198b581279c431bad450deaf7669f87", "40dad62928a4498699eebf9aa7f4be98"),
    CalibrationTestData("1b717cbfe9c34165b18c28a8e9bb746a", "0a129b96d3a3483eb63a507f0452ac58"),
    CalibrationTestData("c748c4754a49402b973999e8f4013533", "ac1ee5f8d2b94fe2bb1206a0e8f44dfa"),
    CalibrationTestData("ef56b5089358479d8e007355933f40dc", "34b35c4e51844611bf27f578cad4fbc9"),
    CalibrationTestData("bc8a9a64b16042a9a7bc383923bd4c8a", "526e1b4441ea49bda0c3ee6bdbd085cd"),
    CalibrationTestData("218364c539044d02bf7994b4e3e174ed", "9f4db3741c2a45979e94196c93e5a331"),
    CalibrationTestData("85004013c0db4fc3860b11f57942f81e", "84cf08668ff84bbd883eaea4e5bd074f"),
  };
}

TEST(Sensors, ReadSensors) {
  const std::string test_file = std::string(TEST_DATA_DIR) + "/" + std::string(TEST_SENSOR_JSON);
  mands::sensors::SensorManager sensorManager;
  ASSERT_TRUE(sensorManager.read_sensors(test_file));
  const auto& sensors = sensorManager.get_sensors();
  ASSERT_EQ(sensors.size(), TEST_SENSORS_TOKENS.size());
  for (size_t i = 0; i < sensorManager.get_sensors().size(); ++i) {
    const auto& sensor = sensors[i];
    ASSERT_EQ(sensor->get_token(), TEST_SENSORS_TOKENS[i]);
  }
}

TEST(Calibrations, ReadCalibrations) {
  const std::string test_file = std::string(TEST_DATA_DIR) + "/" + std::string(TEST_CALIBRATION_JSON);
  mands::sensors::SensorManager sensorManager;
  ASSERT_TRUE(sensorManager.read_calibrations(test_file));
  const auto& calibrations = sensorManager.get_calibrations();
  ASSERT_EQ(calibrations.size(), TEST_CALIBRATION_TOKENS.size());
  for (size_t i = 0; i < calibrations.size(); ++i) {
    const auto& calibrated_sensor = calibrations[i];
    ASSERT_EQ(calibrated_sensor->get_token().value, TEST_CALIBRATION_TOKENS[i].TOKEN);
    ASSERT_EQ(calibrated_sensor->get_sensor_token().value, TEST_CALIBRATION_TOKENS[i].SENSOR_TOKEN);
  }
}

TEST(Modality, StringConversion) {
  ASSERT_EQ(mands::sensors::modality_to_string(mands::sensors::Modality::CAMERA), "camera");
  ASSERT_EQ(mands::sensors::modality_to_string(mands::sensors::Modality::LIDAR), "lidar");
  ASSERT_EQ(mands::sensors::modality_to_string(mands::sensors::Modality::RADAR), "radar");
  ASSERT_EQ(mands::sensors::modality_to_string(mands::sensors::Modality::IMU), "imu");

  ASSERT_EQ(mands::sensors::string_to_modality("camera"), mands::sensors::Modality::CAMERA);
  ASSERT_EQ(mands::sensors::string_to_modality("lidar"), mands::sensors::Modality::LIDAR);
  ASSERT_EQ(mands::sensors::string_to_modality("radar"), mands::sensors::Modality::RADAR);
  ASSERT_EQ(mands::sensors::string_to_modality("imu"), mands::sensors::Modality::IMU);
}