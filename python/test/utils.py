from pathlib import Path

# TODO: define project path via cmake or environment variable
PROJECT_ROOT = Path(__file__).parent.parent.parent
TEST_DATA_DIR = PROJECT_ROOT / "core" / "test" / "data"
