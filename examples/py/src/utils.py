from pathlib import Path

# TODO: define project path via cmake or environment variable
PROJECT_ROOT = Path(__file__).parent.parent.parent.parent
TEST_DATASET_PATH = PROJECT_ROOT / "core" / "test" / "data"

SENCOR_FILE = "sensor.json"