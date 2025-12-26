#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <MANTruckDataset/utils.hpp>

namespace py = pybind11;
namespace man_ds = man::dataset;

void init_utils_bindings(py::module &m) {
  py::class_<man_ds::Token> token(m, "Token", "A class representing a unique identifier token.");
  token.def_readwrite("value", &man_ds::Token::value, "The string representation of the token.");

  token.def(py::init<>())
    .def(py::init<const std::string &>(), py::arg("token_str"))
    .def("__eq__", [](const man_ds::Token& a, const man_ds::Token& b) { return a == b; }, py::is_operator())
    .def("__hash__", [](const man_ds::Token& t) { return std::hash<man_ds::Token>{}(t); });
}
