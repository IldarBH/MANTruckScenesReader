from MANTruckDatasetPy import DataItem, SensorBase, SensorManager
from utils import SENCOR_FILE

if __name__ == "__main__":
  sensor_mgr = SensorManager()
  sensor_mgr.read_sensors(str(SENCOR_FILE))
  print(len(sensor_mgr))
  for sensor in sensor_mgr:
    print(f"Sensor token: {sensor.get_token().value}")