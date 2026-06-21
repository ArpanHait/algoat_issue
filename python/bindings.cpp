#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/optional.h>
#include <algoat/algoat.hpp>
#include <vector>
#include <span>

namespace nb = nanobind;

NB_MODULE(_algoat_impl, m) {
    m.doc() = "Algoat C++ algorithm library bindings";

    m.def("load_global_config", &algoat::load_global_config, nb::arg("filepath"), "Load algorithm configuration from a JSON file");

    m.def("sort", [](std::vector<int> data) -> std::vector<int> {
        algoat::sort<int>(std::span<int>{data});
        return data;
    }, nb::arg("data"), "Sort a list of ints");

    m.def("sort", [](std::vector<double> data) -> std::vector<double> {
        algoat::sort<double>(std::span<double>{data});
        return data;
    }, nb::arg("data"), "Sort a list of floats");

    m.def("search", [](std::vector<int> data, const int& target) -> std::optional<std::size_t> {
        return algoat::search<int>(std::span<int>{data}, target);
    }, nb::arg("data"), nb::arg("target"), "Search for an int");

    m.def("search", [](std::vector<double> data, const double& target) -> std::optional<std::size_t> {
        return algoat::search<double>(std::span<double>{data}, target);
    }, nb::arg("data"), nb::arg("target"), "Search for a float");
}
