#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <MANTruckDataset/Scene.hpp>

namespace py = pybind11;
namespace man_ds = man::dataset;

PYBIND11_MODULE(MANTruckDatasetPy, m) {
  m.doc() = "pybind11 plugin for MANTruckDataset";

  py::class_<man_ds::scenes::Scene>(m, "Scene",
    "A scene object containing metadata about a MAN truck scene")
    .def(py::init<const std::string&, const std::string&, const std::string&, const std::string&, const std::string&>(),
      py::arg("name"), py::arg("description"), py::arg("token"), py::arg("first_sample_token"), py::arg("last_sample_token"),
      "Initialize a Scene object")
    .def("get_name", &man_ds::scenes::Scene::get_name, "Get the scene name")
    .def("get_description", &man_ds::scenes::Scene::get_description, "Get the scene description")
    .def("get_token", &man_ds::scenes::Scene::get_token, "Get the scene token")
    .def("get_first_sample_token", &man_ds::scenes::Scene::get_first_sample_token, "Get the first sample token")
    .def("get_last_sample_token", &man_ds::scenes::Scene::get_last_sample_token, "Get the last sample token")
    .def("__repr__",
      [](const man_ds::scenes::Scene &s) {
        return "<Scene name='" + s.get_name() + "' token='" + s.get_token() + "'>";
      });
  
  py::class_<man_ds::scenes::SceneManager>(m, "SceneManager")
    .def(py::init<>())
    .def("read_scenes", &man_ds::scenes::SceneManager::read_scenes, "Read scenes from a JSON file",
      py::arg("filename"))
    .def("size", 
      &man_ds::scenes::SceneManager::size, "Get the number of scenes loaded")
    .def("__len__", 
      &man_ds::scenes::SceneManager::size)
    .def("__getitem__", 
      &man_ds::scenes::SceneManager::operator[], "Get scene by token",
      py::arg("token"), 
      py::return_value_policy::reference_internal)
    .def("__iter__",
      [](const man_ds::scenes::SceneManager &sm) {
        return py::make_iterator(sm.begin(), sm.end(), py::return_value_policy::reference_internal);
      },
      py::keep_alive<0, 1>());
}