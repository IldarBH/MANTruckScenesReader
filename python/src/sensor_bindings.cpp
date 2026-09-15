#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <MANSensors/sensor_manager.hpp>
#include <MANTruckDataset/utils.hpp>

namespace py = pybind11;
namespace man_ds = man::dataset;

void init_sensor_bindings(py::module &m) {
  py::enum_<man_ds::sensors::Modality> modality(m, "Modality", "Enumeration of sensor modalities");
  modality
    .value("CAMERA", man_ds::sensors::Modality::CAMERA)
    .value("LIDAR", man_ds::sensors::Modality::LIDAR)
    .value("RADAR", man_ds::sensors::Modality::RADAR)
    .value("IMU", man_ds::sensors::Modality::IMU)
    .def("__str__", [](const man_ds::sensors::Modality &m) {
      return man_ds::sensors::resolve_modality_name(m);
  });

  py::class_<man_ds::sensors::SensorBase, man_ds::sensors::SensorBase::SPtr> sensor_base(m, "SensorBase",
    "Base class for sensor objects containing data items");
  sensor_base
    .def(py::init<const man_ds::Token&, const std::string&, const man_ds::sensors::Modality>(),
      py::arg("token"), py::arg("channel"), py::arg("modality"),
      "Initialize a SensorBase object")
    .def(py::init<const man_ds::Token&, const std::string&, const std::string_view>(),
      py::arg("token"), py::arg("channel"), py::arg("modality"),
      "Initialize a SensorBase object")
    .def(py::init<const std::string&, const std::string&, const std::string_view>(),
      py::arg("token"), py::arg("channel"), py::arg("modality"),
      "Initialize a SensorBase object")
    .def("get_token", &man_ds::sensors::SensorBase::get_token,
      "Get the sensor token")
    .def("get_channel", &man_ds::sensors::SensorBase::get_channel,
      "Get the sensor channel")
    .def("get_modality", &man_ds::sensors::SensorBase::get_modality,
      "Get the sensor modality");

  py::class_<man_ds::sensors::SensorManager> sensor_manager(m, "SensorManager",
    "Manager for handling multiple sensors");
  sensor_manager
    .def(py::init<>())
    .def("read_sensors", &man_ds::sensors::SensorManager::read_sensors,
      py::arg("filename"),
      "Read sensors from a JSON file")
    .def("get_sensors", &man_ds::sensors::SensorManager::get_sensors,
      py::return_value_policy::reference_internal,
      "Get all sensors in the manager")
    .def("size", &man_ds::sensors::SensorManager::size,
      "Get the number of sensors loaded")
    .def("__getitem__", py::overload_cast<const size_t>(&man_ds::sensors::SensorManager::operator[], py::const_),
      py::arg("index"),
      "Get a sensor by index")
    .def("__getitem__", py::overload_cast<const man_ds::Token&>(&man_ds::sensors::SensorManager::operator[], py::const_),
      py::arg("token"),
      "Get a sensor by token")
    .def("__len__", &man_ds::sensors::SensorManager::size)
    .def("__iter__",
      [](const man_ds::sensors::SensorManager &sm) {
        return py::make_iterator(sm.cbegin(), sm.cend());
      }, 
      py::keep_alive<0, 1>(),
      "Iterate through all sensors");
}