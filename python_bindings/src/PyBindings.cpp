#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include <toolbox/Algebra/Vectors.hpp>

namespace py = pybind11;
using namespace Toolbox;

PYBIND11_MODULE(CppPricingToolboxPython, m) {
    m.doc() = "pybind11 cross-module test module";

    m.def("add", [](int a, int b) { return a + b; });

    using VecType = DynamicVector<double>;
    
    py::class_<VecType>(m, "DynamicVector")
        .def(py::init<>())
        .def(py::init<size_t>())
        .def(py::init<size_t, double>())
        .def("at", py::overload_cast<size_t>(&VecType::at))
        .def("__add__", [](const VecType& vec1, const VecType& vec2) { return VecType(vec1 + vec2); })
        .def("__sub__", [](const VecType& vec1, const VecType& vec2) { return VecType(vec1 - vec2); })
        .def("__mul__", [](const VecType& vec1, const VecType& vec2) { return VecType(vec1 * vec2); })
        .def("__truediv__", [](const VecType& vec1, const VecType& vec2) { return VecType(vec1 / vec2); })
        .def("__getitem__", [](VecType& vec, const size_t& idx) { return vec[idx]; })
        .def("__setitem__", [](VecType& vec, const size_t& idx, const double& value) { vec[idx] = value; })
        .def("__repr__", &VecType::toString);
}