#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <MANTruckDataset/MANTruckDataset.hpp>

#include <vector>
#include <string>

namespace py = pybind11;
namespace man_ds = man::dataset;

void init_dataset_bindings(py::module &m) {
  py::class_<man_ds::MANTruckDataset>(m, "MANTruckDataset",
    "Main class for accessing the MAN Truck Dataset")
    .def(py::init<const std::string&, const std::string&, const std::string&, const std::vector<std::string>&>(),
      py::arg("datasets_folder"),
      py::arg("dataset_name"),
      py::arg("scene_token"),
      py::arg("sensor_tokens") = std::vector<std::string>{})
    .def("get_sensor_manager",
      &man_ds::MANTruckDataset::get_sensor_manager,
      py::return_value_policy::reference_internal,
      "Get the sensor manager containing all loaded sensors");
}