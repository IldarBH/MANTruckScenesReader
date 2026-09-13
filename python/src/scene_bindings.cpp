#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <MANTruckDataset/Scene.hpp>
#include <MANTruckDataset/utils.hpp>


namespace py = pybind11;
namespace man_ds = man::dataset;

void init_scene_bindings(py::module &m) {
  py::class_<man_ds::scenes::Scene, man_ds::scenes::Scene::SPtr> scene(m, "Scene", "A scene object containing metadata about a MAN truck scene");
  scene
    .def(py::init<const std::string&, const std::string&, const std::string&, const std::string&, const std::string&>(),
      py::arg("name"), py::arg("description"), py::arg("token"), py::arg("first_sample_token"), py::arg("last_sample_token"))
    .def(py::init<const std::string&, const std::string&, const man_ds::Token&, const man_ds::Token&, const man_ds::Token&>(),
      py::arg("name"), py::arg("description"), py::arg("token"), py::arg("first_sample_token"), py::arg("last_sample_token"))
    .def("get_name", &man_ds::scenes::Scene::get_name)
    .def("get_description", &man_ds::scenes::Scene::get_description)
    .def("get_token", &man_ds::scenes::Scene::get_token)
    .def("get_first_sample_token", &man_ds::scenes::Scene::get_first_sample_token)
    .def("get_last_sample_token", &man_ds::scenes::Scene::get_last_sample_token);
  
  py::class_<man_ds::scenes::SceneManager> scene_manager(m, "SceneManager");
  scene_manager
    .def(py::init<>())
    .def("read_scenes", &man_ds::scenes::SceneManager::read_scenes, py::arg("filename"))
    .def("add_scene", 
      py::overload_cast<const std::string&, const std::string&, const std::string&, const std::string&, const std::string&>(&man_ds::scenes::SceneManager::add_scene),
      py::arg("name"),
      py::arg("description"),
      py::arg("token"),
      py::arg("first_sample_token"),
      py::arg("last_sample_token"))
    .def("add_scene",
      py::overload_cast<const std::string&, const std::string&, const man_ds::Token&, const man_ds::Token&, const man_ds::Token&>(&man_ds::scenes::SceneManager::add_scene),
      py::arg("name"),
      py::arg("description"),
      py::arg("token"),
      py::arg("first_sample_token"),
      py::arg("last_sample_token"))
    .def("get_scenes", &man_ds::scenes::SceneManager::get_scenes, 
      py::return_value_policy::reference_internal)
    .def("size", &man_ds::scenes::SceneManager::size)
    .def("__len__", &man_ds::scenes::SceneManager::size)
    .def("__getitem__",
      py::overload_cast<const size_t>(&man_ds::scenes::SceneManager::operator[], py::const_),
      py::arg("id"),
      py::return_value_policy::reference_internal)
    .def("__getitem__",
      py::overload_cast<const man_ds::Token&>(&man_ds::scenes::SceneManager::operator[], py::const_),
      py::arg("token"),
      py::return_value_policy::reference_internal)
    .def("__iter__",
      [](const man_ds::scenes::SceneManager &sm) {
        const auto &scenes = sm.get_scenes(); 
        return py::make_iterator(scenes.cbegin(), scenes.cend());
      }, py::keep_alive<0, 1>());
}