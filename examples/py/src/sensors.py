from MANTruckDatasetPy import Modality, SensorBase, SensorManager
from utils import TEST_DATASET_PATH, SENCOR_FILE

from pathlib import Path

if __name__ == "__main__":
    sensor_file_path = Path(TEST_DATASET_PATH) / SENCOR_FILE
    sensor_m = SensorManager()
    if (not sensor_m.read_sensors(str(sensor_file_path))):
        print(f"Failed to read sensors from file: {sensor_file_path}")
        exit(1)

    for sensor in sensor_m.get_sensors():
        print(f"Sensor:\n\t{sensor.get_token().value}\n\t{sensor.get_channel()}\n\t{sensor.get_modality()}")