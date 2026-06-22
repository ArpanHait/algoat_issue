#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/optional.h>
#include <algoat/algoat.hpp>
#include <vector>
#include <span>

namespace nb = nanobind;

struct PyIntWrapper {
    PyObject* obj;
    long long val;

    PyIntWrapper() : obj(nullptr), val(0) {}
    PyIntWrapper(PyObject* o) : obj(o) {
        if (PyLong_Check(o)) val = PyLong_AsLongLong(o);
        else val = (long long)PyFloat_AsDouble(o);
    }

    bool operator<(const PyIntWrapper& other) const { return val < other.val; }
    bool operator<=(const PyIntWrapper& other) const { return val <= other.val; }
    bool operator>(const PyIntWrapper& other) const { return val > other.val; }
    bool operator>=(const PyIntWrapper& other) const { return val >= other.val; }
    bool operator==(const PyIntWrapper& other) const { return val == other.val; }
};

struct PyFloatWrapper {
    PyObject* obj;
    double val;

    PyFloatWrapper() : obj(nullptr), val(0.0) {}
    PyFloatWrapper(PyObject* o) : obj(o) {
        if (PyFloat_Check(o)) val = PyFloat_AsDouble(o);
        else val = (double)PyLong_AsLongLong(o);
    }

    bool operator<(const PyFloatWrapper& other) const { return val < other.val; }
    bool operator<=(const PyFloatWrapper& other) const { return val <= other.val; }
    bool operator>(const PyFloatWrapper& other) const { return val > other.val; }
    bool operator>=(const PyFloatWrapper& other) const { return val >= other.val; }
    bool operator==(const PyFloatWrapper& other) const { return val == other.val; }
};

template<typename Wrapper>
nb::list sort_list_direct(nb::list data) {
    size_t n = nb::len(data);
    std::vector<Wrapper> buf(n);
    for (size_t i = 0; i < n; ++i) {
        buf[i] = Wrapper(data[i].ptr());
    }
    
    algoat::sort<Wrapper>(std::span<Wrapper>{buf});
    
    nb::list result = nb::steal<nb::list>(PyList_New(n));
    for (size_t i = 0; i < n; ++i) {
        PyObject* obj = buf[i].obj;
        Py_INCREF(obj);
        PyList_SET_ITEM(result.ptr(), i, obj);
    }
    return result;
}

template<typename Wrapper>
void sort_list_inplace_impl(nb::list data) {
    size_t n = nb::len(data);
    if (n == 0) return;
    
    std::vector<Wrapper> buf(n);
    for (size_t i = 0; i < n; ++i) {
        buf[i] = Wrapper(data[i].ptr());
    }
    
    algoat::sort<Wrapper>(std::span<Wrapper>{buf});
    
    for (size_t i = 0; i < n; ++i) {
        PyList_SET_ITEM(data.ptr(), i, buf[i].obj);
    }
}

void sort_inplace_dispatch(nb::list data) {
    if (nb::len(data) == 0) return;
    if (PyFloat_Check(data[0].ptr())) {
        sort_list_inplace_impl<PyFloatWrapper>(data);
    } else {
        sort_list_inplace_impl<PyIntWrapper>(data);
    }
}

nb::list sort_dispatch(nb::list data) {
    if (nb::len(data) == 0) return nb::list();
    if (PyFloat_Check(data[0].ptr())) {
        return sort_list_direct<PyFloatWrapper>(data);
    } else {
        return sort_list_direct<PyIntWrapper>(data);
    }
}

template<typename T>
std::optional<std::size_t> search_list_direct(nb::list data, const T& target) {
    std::string algo_name = algoat::get_global_config().searching.prefer.value_or("auto");
    
    if (algo_name == "auto" || algo_name == "binarysearch") {
        size_t lo = 0, hi = nb::len(data);
        while (lo < hi) {
            size_t mid = lo + (hi - lo) / 2;
            T val = nb::cast<T>(data[mid]);
            if (val == target) return mid;
            if (val < target) lo = mid + 1;
            else hi = mid;
        }
        return std::nullopt;
    } else if (algo_name == "linearsearch") {
        size_t n = nb::len(data);
        for (size_t i = 0; i < n; ++i) {
            if (nb::cast<T>(data[i]) == target) return i;
        }
        return std::nullopt;
    } else {
        std::vector<T> vec(nb::len(data));
        for (size_t i = 0; i < nb::len(data); ++i) {
            vec[i] = nb::cast<T>(data[i]);
        }
        return algoat::search<T>(std::span<T>{vec}, target);
    }
}

std::optional<std::size_t> search_dispatch(nb::list data, nb::object target) {
    if (nb::len(data) == 0) return std::nullopt;
    
    if (PyFloat_Check(data[0].ptr()) || PyFloat_Check(target.ptr())) {
        return search_list_direct<double>(data, nb::cast<double>(target));
    } else {
        return search_list_direct<int>(data, nb::cast<int>(target));
    }
}

NB_MODULE(_algoat_impl, m) {
    m.doc() = "Algoat C++ algorithm library bindings";

    m.def("load_global_config", &algoat::load_global_config, nb::arg("filepath"), "Load algorithm configuration from a JSON file");

    m.def("sort", &sort_dispatch, nb::arg("data"), "Sort a list of ints or floats");
    m.def("sort_inplace", &sort_inplace_dispatch, nb::arg("data"), "Sort a list of ints or floats in-place");
    m.def("search", &search_dispatch, nb::arg("data"), nb::arg("target"), "Search for a target in a list");
}
