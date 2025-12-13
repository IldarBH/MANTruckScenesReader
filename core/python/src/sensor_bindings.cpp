#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <MANTruckDataset/Sensor.hpp>

namespace py = pybind11;
namespace man_ds = man::dataset;

void init_sensor_bindings(py::module &m) {
  py::class_<man_ds::sensors::DataItem, man_ds::sensors::DataItem::SPtr>(m, "DataItem",
    "A data item representing a timestamped file in a sensor")
    .def(py::init<const size_t, const std::string&>(),
      py::arg("timestamp"),
      py::arg("filename"),
      "Initialize a DataItem object")
    .def("get_timestamp", &man_ds::sensors::DataItem::get_timestamp,
      "Get the timestamp of the data item")
    .def("get_filename", &man_ds::sensors::DataItem::get_filename,
      "Get the filename of the data item")
    .def("get_prev_sample", &man_ds::sensors::DataItem::get_prev_sample,
      py::return_value_policy::reference_internal,
      "Get the previous data item in the sequence")
    .def("get_next_sample", &man_ds::sensors::DataItem::get_next_sample,
      py::return_value_policy::reference_internal,
      "Get the next data item in the sequence");

  py::class_<man_ds::sensors::SensorBase>(m, "SensorBase",
    "Base class for sensor objects containing data items")
    .def(py::init<const std::string&, const std::string&, const std::string_view>(),
      py::arg("token"),
      py::arg("channel"),
      py::arg("modality"),
      "Initialize a SensorBase object")
    .def("get_token", &man_ds::sensors::SensorBase::get_token,
      "Get the sensor token")
    .def("get_channel", &man_ds::sensors::SensorBase::get_channel,
      "Get the sensor channel")
    .def("get_modality", &man_ds::sensors::SensorBase::get_modality,
      "Get the sensor modality")
    .def("size", &man_ds::sensors::SensorBase::size,
      "Get the number of data items in the sensor")
    .def("add_file", &man_ds::sensors::SensorBase::add_file,
      py::arg("filename"),
      py::arg("timestamp"),
      "Add a data file to the sensor")
    .def("__getitem__", 
      [](const man_ds::sensors::SensorBase &sensor, const size_t index) {
        return sensor[index];
      },
      py::arg("index"),
      "Get a data item by index")
    .def("__len__", &man_ds::sensors::SensorBase::size)
    .def("__repr__",
      [](const man_ds::sensors::SensorBase &sensor) {
        return "<SensorBase token='" + sensor.get_token() + "' channel='" + 
               sensor.get_channel() + "' modality='" + sensor.get_modality() + "'>";
      });

  py::class_<man_ds::sensors::SensorManager>(m, "SensorManager",
    "Manager for handling multiple sensors")
    .def(py::init<>())
    .def("read_sensors", &man_ds::sensors::SensorManager::read_sensors,
      py::arg("filename"),
      py::arg("filter_tokens") = std::vector<std::string>(),
      "Read sensors from a JSON file with optional token filtering")
    .def("add_sensor", &man_ds::sensors::SensorManager::add_sensor,
      py::arg("token"),
      py::arg("channel"),
      py::arg("modality"),
      "Add a sensor to the manager")
    .def("size", &man_ds::sensors::SensorManager::size,
      "Get the number of sensors loaded")
    .def("__len__", &man_ds::sensors::SensorManager::size)
    .def("__getitem__", 
      py::overload_cast<const std::string&>(&man_ds::sensors::SensorManager::operator[]), 
      py::arg("token"),
      py::return_value_policy::reference_internal,
      "Get a sensor by token")
    .def("__iter__",
      [](const man_ds::sensors::SensorManager &sm) {
        return py::make_iterator(sm.begin(), sm.end(), py::return_value_policy::reference_internal);
      },
      py::keep_alive<0, 1>(),
      "Iterate through all sensors");
}