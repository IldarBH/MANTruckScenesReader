#include <MANTruckDataset/utils.hpp>
#include <MANScenes/scene_manager.hpp>

#include <gtest/gtest.h>

#include <unordered_set>
#include <string_view>

#ifndef TEST_DATA_DIR
#define TEST_DATA_DIR "data"
#endif

namespace mands = man::dataset;

namespace{
  constexpr std::string_view TEST_JSON = "scene.json";
  const std::unordered_set<std::string> TEST_SCENES_TOKENS = {
    "044c648ac12345f1aedf33c9f91cdc5a",
    "37355c547904491481e47accc094d567",
    "81f0a41d0a7a44e0ae8f8ea0ade95fdf",
    "b71e2b6ba3fa4279b36bfd4b9720251e",
    "fb0a3d4e84c74b07ba0997891ed12f0b",
    "9fb76bae00124c85aaf4d6d0e4dbf194",
    "38d4ba33fce94499be34f32d245113ed",
    "d0b02e67e97a435192bf43f7bb0f902c",
    "b13b6eb5c4bf4479a631372af53baf28",
    "073e6bb18188424ea9981e3845df54a6"
  };
}

TEST(Scenes, ReadScenes) {
  const std::string test_file = std::string(TEST_DATA_DIR) + "/" + std::string(TEST_JSON);
  mands::scenes::SceneManager scenesManager;
  ASSERT_EQ(scenesManager.read_scenes(test_file), TEST_SCENES_TOKENS.size());
  const auto& scenes = scenesManager.get_scenes();
  ASSERT_EQ(scenes.size(), TEST_SCENES_TOKENS.size());
  for (auto& scene : scenes) {
    ASSERT_TRUE(TEST_SCENES_TOKENS.find(scene->TOKEN.value) != TEST_SCENES_TOKENS.end());
  }
}