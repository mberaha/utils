#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/eigen.h>

#include "math_utils/cpp/stirling_numbers.hpp"

#include "mcmc_utils/cpp/distributions.hpp"
#include "mcmc_utils/cpp/updates.hpp"

namespace py = pybind11;

py::module base("fast_utils", "Utilities in C++, now exported");
py::module math = base.def_submodule("math", "Math utils");
py::module mcmc = base.def_submodule("mcmc", "MCMC utils");


PYBIND11_MODULE(fast_utils, m) {
    m.doc() = "aaa"; // optional module docstring

    auto math = m.def_submodule("math");
    math.def("stirling", &stirling);

    auto mcmc = m.def_submodule("mcmc");
    mcmc.def("normalGammaUpdate", &updates::normalGammaUpdate);
    mcmc.def("simpleLinearRegressionUpdate",
             &updates::simpleLinearRegressionUpdate);
    mcmc.def("heteroSchedLinearRegressionUpdate",
             &updates::heteroSchedLinearRegressionUpdate);
    mcmc.def("trunc_normal_lpdf",
             &distributions::trunc_normal_lpdf);
    mcmc.def("marginal_normal_gamma_lpdf",
             &distributions::marginal_normal_gamma_lpdf);
}
