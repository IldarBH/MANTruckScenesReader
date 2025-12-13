from pathlib import Path

DATASET_PATH = Path("/workspace/Sandbox/data/man-truckscenes")
DATASET_NAME = "v1.0-mini"
SCENE_FILE = DATASET_PATH / DATASET_NAME / "scene.json"
SAMPLE_FILE = DATASET_PATH / DATASET_NAME / "sample.json"
SENCOR_FILE = DATASET_PATH / DATASET_NAME / "sensor.json"