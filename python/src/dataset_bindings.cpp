#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <MANTruckDataset/MANTruckDataset.hpp>

#include <vector>
#include <string>

namespace py = pybind11;
namespace man_ds = man::dataset;

void init_dataset_bindings(py::module &m) {
  py::class_<man_ds::MANTruckDataset>(
    m,
    "MANTruckDataset",
    "Main class for accessing the MAN Truck Dataset")
    .def(
      py::init<const std::string&, const std::string&>(),
      py::arg("dataset_folder"),
      py::arg("metadata_folder"),
      "Create a MANTruckDataset loader for a dataset folder and metadata folder")
    .def(
      "get_scene_manager",
      &man_ds::MANTruckDataset::get_scene_manager,
      py::return_value_policy::reference_internal,
      "Get the scene manager")
    .def(
      "get_sensor_manager",
      &man_ds::MANTruckDataset::get_sensor_manager,
      py::return_value_policy::reference_internal,
      "Get the sensor manager containing all loaded sensors")
    .def(
      "get_calibration_manager",
      &man_ds::MANTruckDataset::get_calibration_manager,
      py::return_value_policy::reference_internal,
      "Get the calibration manager")
    .def(
      "get_sample_manager",
      &man_ds::MANTruckDataset::get_sample_manager,
      py::return_value_policy::reference_internal,
      "Get the sample manager")
    .def(
      "get_data_manager",
      &man_ds::MANTruckDataset::get_data_manager,
      py::return_value_policy::reference_internal,
      "Get the data manager")
    .def(
      "get_data",
      [](const man_ds::MANTruckDataset& dataset,
         const man_ds::scenes::Scene& scene,
         const man_ds::sensors::SensorBase& sensor) {
        py::list result;
        for (const auto& item : dataset.get_data(scene, sensor)) {
          if (auto sample = item.lock()) {
            result.append(sample);
          }
        }
        return result;
      },
      py::arg("scene"),
      py::arg("sensor"),
      "Get data samples for a scene and sensor");
}