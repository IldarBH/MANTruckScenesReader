from MANTruckDatasetPy import Token, SensorBase, SensorManager
from utils import TEST_DATA_DIR
from pathlib import Path

TEST_SENCOR_JSON = "sensor.json"
TEST_SENSOR_TOKENS = [
    Token("b3dd3279d239492195f64963ec70b244"),
    Token("c7b216f6c0c2426ea01e20ffb50ecfb0"),
    Token("27587edfa74844ce931a710995531ca9"),
    Token("fb5519c659a5400c8e9bbf6ec2e50528"),
    Token("0785ec5f7a5e4c93a99fea2ad781783d"),
    Token("e70adcb9ee16435abc316cfd73c58fd7"),
    Token("1c4f2bbb64f847a193c748c1c14f0574"),
    Token("fe19aa64da874708a8cd417103e7cdc7"),
    Token("3f53edcde9e44caaba5e689726c7aab7"),
    Token("9ecd75e3eaf643d5b1d5a6cefba7f1f3"),
    Token("fcddf720b15b4bc3b59eef0bdf3e0f94"),
    Token("40dad62928a4498699eebf9aa7f4be98"),
    Token("0a129b96d3a3483eb63a507f0452ac58"),
    Token("ac1ee5f8d2b94fe2bb1206a0e8f44dfa"),
    Token("34b35c4e51844611bf27f578cad4fbc9"),
    Token("526e1b4441ea49bda0c3ee6bdbd085cd"),
    Token("9f4db3741c2a45979e94196c93e5a331"),
    Token("84cf08668ff84bbd883eaea4e5bd074f")
]

def test_LoadFromJson():
    test_sensor_file = Path(TEST_DATA_DIR) / TEST_SENCOR_JSON
    sensor_manager = SensorManager()
    assert sensor_manager.read_sensors(str(test_sensor_file)) == True, f"Failed to load sensor data from {test_sensor_file}"
    assert len(sensor_manager) == len(TEST_SENSOR_TOKENS), f"Expected {len(TEST_SENSOR_TOKENS)} sensors, but got {sensor_manager.size()}"
    assert sensor_manager.size() == len(TEST_SENSOR_TOKENS), f"Expected {len(TEST_SENSOR_TOKENS)} sensors, but got {sensor_manager.size()}"
    for i in range(len(TEST_SENSOR_TOKENS)):
        sensor: SensorBase = sensor_manager[i]
        assert sensor.get_token() == TEST_SENSOR_TOKENS[i], f"Sensor token mismatch at index {i}: expected {TEST_SENSOR_TOKENS[i]}, got {sensor.get_token()}"

