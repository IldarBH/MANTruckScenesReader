#include <pybind11/pybind11.h>

namespace py = pybind11;

// Forward declarations
void init_scene_bindings(py::module &m);
void init_sample_bindings(py::module &m);
void init_sensor_bindings(py::module &m);

PYBIND11_MODULE(MANTruckDatasetPy, m) {
  m.doc() = "MANTruckDataset Python bindings";
  
  init_scene_bindings(m);
  init_sample_bindings(m);
  init_sensor_bindings(m);
}