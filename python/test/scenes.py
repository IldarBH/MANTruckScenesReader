from pathlib import Path

from MANTruckDatasetPy import Scene, SceneManager, Token
from utils import TEST_DATA_DIR


TEST_SCENE_JSON = "scene.json"
TEST_SCENE_TOKENS = [
    Token("044c648ac12345f1aedf33c9f91cdc5a"),
    Token("37355c547904491481e47accc094d567"),
    Token("81f0a41d0a7a44e0ae8f8ea0ade95fdf"),
    Token("b71e2b6ba3fa4279b36bfd4b9720251e"),
    Token("fb0a3d4e84c74b07ba0997891ed12f0b"),
    Token("9fb76bae00124c85aaf4d6d0e4dbf194"),
    Token("38d4ba33fce94499be34f32d245113ed"),
    Token("d0b02e67e97a435192bf43f7bb0f902c"),
    Token("b13b6eb5c4bf4479a631372af53baf28"),
    Token("073e6bb18188424ea9981e3845df54a6"),
]


def test_LoadFromJson():
    test_scene_file = Path(TEST_DATA_DIR) / TEST_SCENE_JSON
    scene_manager = SceneManager()

    assert scene_manager.read_scenes(str(test_scene_file)) == len(TEST_SCENE_TOKENS), \
        f"Failed to load scene data from {test_scene_file}"
    assert len(scene_manager) == len(TEST_SCENE_TOKENS), \
        f"Expected {len(TEST_SCENE_TOKENS)} scenes, but got {scene_manager.size()}"
    assert scene_manager.size() == len(TEST_SCENE_TOKENS), \
        f"Expected {len(TEST_SCENE_TOKENS)} scenes, but got {scene_manager.size()}"

    for i in range(len(TEST_SCENE_TOKENS)):
        scene: Scene = scene_manager[i]
        assert (scene.get_token() == TEST_SCENE_TOKENS[i]), \
            f"Scene token mismatch at index {i}: expected {TEST_SCENE_TOKENS[i]}, got {scene.get_token()}"