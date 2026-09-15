from pathlib import Path

from MANTruckDatasetPy import Sample, SampleManager, Token
from utils import TEST_DATA_DIR


TEST_SCENE_JSON = "sample.json"
TEST_JSON_SAMPLES_COUNT = 400


def test_LoadFromJson():
    test_scene_file = Path(TEST_DATA_DIR) / TEST_SCENE_JSON
    scene_manager = SampleManager()
    assert scene_manager.read_samples(str(test_scene_file)) == TEST_JSON_SAMPLES_COUNT
