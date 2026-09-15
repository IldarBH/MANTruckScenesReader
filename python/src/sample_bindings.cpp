#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <MANTruckDataset/Sample.hpp>

namespace py = pybind11;
namespace man_ds = man::dataset;

void init_sample_bindings(py::module &m) {
  py::class_<man_ds::samples::Sample, man_ds::samples::Sample::SPtr> sample(m, "Sample",
    "A sample object representing a timestamped measurement in a scene");
  sample
  .def(py::init<const man_ds::Token&, const man_ds::Token&, const int64_t>(),
    py::arg("token"), py::arg("scene_token"), py::arg("timestamp"), 
    "Initialize a Sample object")
  .def(py::init<const man_ds::samples::Sample>(),
    py::arg("sample"), "Initialize a Sample object")
  .def("get_token", &man_ds::samples::Sample::get_token,
    "Get the sample token")
  .def("get_scene_token", &man_ds::samples::Sample::get_scene_token,
    "Get the scene token this sample belongs to")
  .def("get_timestamp", &man_ds::samples::Sample::get_timestamp,
    "Get the sample timestamp")
  .def("get_prev_sample", &man_ds::samples::Sample::get_prev_sample,
    py::return_value_policy::reference_internal,
    "Get the previous sample in the sequence")
  .def("get_next_sample", &man_ds::samples::Sample::get_next_sample,
    py::return_value_policy::reference_internal,
    "Get the next sample in the sequence")
  .def("set_prev_sample", &man_ds::samples::Sample::set_prev_sample,
    py::arg("prev"),
    "Set the previous sample in the sequence")
  .def("set_next_sample", &man_ds::samples::Sample::set_next_sample,
    py::arg("next"),
    "Set the next sample in the sequence");

  py::class_<man_ds::samples::SampleManager> sample_manager(m, "SampleManager",
    "Manager for handling a sequence of samples in a scene");
  sample_manager
    .def(py::init<>())
    .def("read_samples",
      &man_ds::samples::SampleManager::read_samples,
      py::arg("filename"),
      "Read samples from a JSON file")
    .def("add_sample",
      &man_ds::samples::SampleManager::add_sample,
      py::arg("token"),
      py::arg("scene_token"),
      py::arg("timestamp"),
      py::arg("prev_token") = man_ds::Token{},
      py::arg("next_token") = man_ds::Token{},
      "Add a sample with optional prev/next links")
    .def("size",
      &man_ds::samples::SampleManager::size,
      "Get the number of samples")
    .def("__len__",
      &man_ds::samples::SampleManager::size)
    .def("__getitem__",
      (const man_ds::samples::Sample& (man_ds::samples::SampleManager::*)(std::size_t) const)
        &man_ds::samples::SampleManager::operator[],
      py::arg("index"),
      py::return_value_policy::reference_internal,
      "Get a sample by index")
    .def("get_samples",
      [](const man_ds::samples::SampleManager& manager) {
        return manager.get_samples();
      },
      py::return_value_policy::reference_internal,
      "Get all samples")
    .def("get_samples_by_scene",
      [](const man_ds::samples::SampleManager& manager, const man_ds::Token& scene_token) {
        py::list result;
        for (const auto& sample_ref : manager.get_samples_by_scene(scene_token)) {
          if (auto sample = sample_ref.lock()) {
            result.append(sample);
          }
        }
        return result;
      },
      py::arg("scene_token"),
      "Get all samples for a scene token")
    .def("__iter__",
      [](const man_ds::samples::SampleManager &manager) {
        return py::make_iterator(manager.cbegin(), manager.cend());
      },
      py::keep_alive<0, 1>(),
      "Iterate through all samples");
}