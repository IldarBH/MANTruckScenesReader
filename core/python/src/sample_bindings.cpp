#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <MANTruckDataset/Sample.hpp>

namespace py = pybind11;
namespace man_ds = man::dataset;

void init_sample_bindings(py::module &m) {
  py::class_<man_ds::samples::Sample, man_ds::samples::Sample::SPtr>(m, "Sample",
    "A sample object representing a timestamped measurement in a scene")
    .def(py::init<const std::string&, const std::string&, const int64_t>(),
      py::arg("token"),
      py::arg("scene_token"),
      py::arg("timestamp"),
      "Initialize a Sample object")
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
      "Set the next sample in the sequence")
    .def("__repr__",
      [](const man_ds::samples::Sample &s) {
        return "<Sample token='" + s.get_token() + "' scene_token='" + 
               s.get_scene_token() + "' timestamp=" + std::to_string(s.get_timestamp()) + ">";
      });

  py::class_<man_ds::samples::SampleSequence>(m, "SampleSequence",
    "Manager for handling a sequence of samples in a scene")
    .def(py::init<>())
    .def("read_samples", &man_ds::samples::SampleSequence::read_samples,
      py::arg("filename"),
      py::arg("scene_token"),
      "Read samples from a JSON file filtered by scene token")
    .def("add_sample",
      (void (man_ds::samples::SampleSequence::*)(
        const std::string&, const std::string&, const int64_t, 
        const std::string&, const std::string&))
      &man_ds::samples::SampleSequence::add_sample,
      py::arg("token"),
      py::arg("scene_token"),
      py::arg("timestamp"),
      py::arg("prev_token") = "",
      py::arg("next_token") = "",
      "Add a sample to the sequence with optional prev/next linking")
    .def("size", &man_ds::samples::SampleSequence::size,
      "Get the number of samples in the sequence")
    .def("__len__", &man_ds::samples::SampleSequence::size)
    .def("__getitem__",
      (const man_ds::samples::Sample& (man_ds::samples::SampleSequence::*)(std::size_t) const)
      &man_ds::samples::SampleSequence::operator[],
      py::arg("index"),
      py::return_value_policy::reference_internal,
      "Get a sample by index")
    .def("get_tokens", &man_ds::samples::SampleSequence::get_tokens,
      "Get list of all sample tokens")
    .def("__iter__",
      [](const man_ds::samples::SampleSequence &seq) {
        return py::make_iterator(seq.begin(), seq.end());
      },
      py::keep_alive<0, 1>(),
      "Iterate through all samples in sequence");
}