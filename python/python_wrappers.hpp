#pragma once

#include <Python.h>
#include <vector>
#include <cstdint>
#include <cstring>
#include <string_view>
#include <algoat/numerics/morton.hpp>

namespace algoat {
namespace pybind {

struct PyComplexWrapper {
    PyObject* obj;
    std::complex<float> val;

    PyComplexWrapper() : obj(nullptr), val(0.0f, 0.0f) {}
    PyComplexWrapper(PyObject* o) : obj(o) {
        if (PyComplex_Check(o)) {
            val = std::complex<float>(
                static_cast<float>(PyComplex_RealAsDouble(o)),
                static_cast<float>(PyComplex_ImagAsDouble(o))
            );
        } else {
            val = std::complex<float>(0.0f, 0.0f);
        }
    }

    bool operator<(const PyComplexWrapper& other) const { return algoat::numerics::MortonCompare{}(val, other.val); }
    bool operator==(const PyComplexWrapper& other) const { return val == other.val; }
    bool operator>(const PyComplexWrapper& other) const { return other < *this; }
    bool operator<=(const PyComplexWrapper& other) const { return !(*this > other); }
    bool operator>=(const PyComplexWrapper& other) const { return !(*this < other); }
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

struct PyBigIntWrapper {
    PyObject* obj;
    int64_t small_val;
    bool is_small;
    int sign;
    std::vector<uint64_t> limbs;

    PyBigIntWrapper() : obj(nullptr), small_val(0), is_small(true), sign(0) {}
    PyBigIntWrapper(PyObject* o) : obj(o), small_val(0), is_small(true), sign(0) {
        if (PyLong_Check(o)) {
            int overflow = 0;
            long long v = PyLong_AsLongLongAndOverflow(o, &overflow);
            if (overflow == 0) {
                small_val = static_cast<int64_t>(v);
                is_small = true;
            } else {
                is_small = false;
                PyObject* zero = PyLong_FromLong(0);
                int is_less = PyObject_RichCompareBool(o, zero, Py_LT);
                Py_DECREF(zero);
                sign = (is_less == 1) ? -1 : 1;
                
                size_t num_bits = _PyLong_NumBits(o);
                size_t num_bytes = (num_bits + 7) / 8;
                size_t num_limbs = (num_bytes + 7) / 8;
                if (num_limbs == 0) num_limbs = 1;
                limbs.resize(num_limbs, 0);
                
#if PY_VERSION_HEX >= 0x030D0000
                _PyLong_AsByteArray((PyLongObject*)o, (unsigned char*)limbs.data(), num_limbs * 8, 1, 0, 0);
#else
                _PyLong_AsByteArray((PyLongObject*)o, (unsigned char*)limbs.data(), num_limbs * 8, 1, 0);
#endif
            }
        } else if (PyFloat_Check(o)) {
            small_val = static_cast<int64_t>(PyFloat_AsDouble(o));
            is_small = true;
        }
    }

    static int compare_limbs(const std::vector<uint64_t>& a, const std::vector<uint64_t>& b) {
        if (a.size() < b.size()) return -1;
        if (a.size() > b.size()) return 1;
        for (ssize_t i = static_cast<ssize_t>(a.size()) - 1; i >= 0; --i) {
            if (a[i] < b[i]) return -1;
            if (a[i] > b[i]) return 1;
        }
        return 0;
    }

    int get_sign() const { return is_small ? ((small_val > 0) - (small_val < 0)) : sign; }

    bool operator<(const PyBigIntWrapper& other) const {
        if (is_small && other.is_small) return small_val < other.small_val;
        int s1 = get_sign(), s2 = other.get_sign();
        if (s1 != s2) return s1 < s2;
        if (s1 == 0) return false;
        if (is_small && !other.is_small) return s1 > 0;
        if (!is_small && other.is_small) return s1 < 0;
        int cmp = compare_limbs(limbs, other.limbs);
        return (s1 > 0) ? (cmp < 0) : (cmp > 0);
    }
    bool operator<=(const PyBigIntWrapper& other) const {
        return *this < other || *this == other;
    }
    bool operator>(const PyBigIntWrapper& other) const {
        return other < *this;
    }
    bool operator>=(const PyBigIntWrapper& other) const {
        return !(*this < other);
    }
    bool operator==(const PyBigIntWrapper& other) const {
        if (is_small && other.is_small) return small_val == other.small_val;
        if (is_small != other.is_small) return false;
        int s1 = get_sign(), s2 = other.get_sign();
        if (s1 != s2) return false;
        return compare_limbs(limbs, other.limbs) == 0;
    }
};

struct PyStringWrapper {
    PyObject* obj;
    std::string_view sv;

    PyStringWrapper() : obj(nullptr), sv() {}
    PyStringWrapper(PyObject* o) : obj(o) {
        if (PyUnicode_Check(o)) {
            Py_ssize_t len = 0;
            const char* ptr = PyUnicode_AsUTF8AndSize(o, &len);
            if (ptr) sv = std::string_view(ptr, len);
        }
    }
    bool operator<(const PyStringWrapper& other) const {
        if (obj == other.obj) return false;
        return sv < other.sv;
    }
    bool operator<=(const PyStringWrapper& other) const {
        if (obj == other.obj) return true;
        return sv <= other.sv;
    }
    bool operator>(const PyStringWrapper& other) const {
        if (obj == other.obj) return false;
        return sv > other.sv;
    }
    bool operator>=(const PyStringWrapper& other) const {
        if (obj == other.obj) return true;
        return sv >= other.sv;
    }
    bool operator==(const PyStringWrapper& other) const {
        if (obj == other.obj) return true;
        return sv == other.sv;
    }
};

struct PyGenericWrapper {
    PyObject* obj;

    PyGenericWrapper() : obj(nullptr) {}
    PyGenericWrapper(PyObject* o) : obj(o) {}

    bool operator<(const PyGenericWrapper& other) const {
        PyGILState_STATE gstate = PyGILState_Ensure();
        int res = PyObject_RichCompareBool(obj, other.obj, Py_LT);
        if (res == -1) { PyErr_Clear(); res = 0; }
        PyGILState_Release(gstate);
        return res == 1;
    }
    bool operator<=(const PyGenericWrapper& other) const {
        PyGILState_STATE gstate = PyGILState_Ensure();
        int res = PyObject_RichCompareBool(obj, other.obj, Py_LE);
        if (res == -1) { PyErr_Clear(); res = 0; }
        PyGILState_Release(gstate);
        return res == 1;
    }
    bool operator>(const PyGenericWrapper& other) const {
        PyGILState_STATE gstate = PyGILState_Ensure();
        int res = PyObject_RichCompareBool(obj, other.obj, Py_GT);
        if (res == -1) { PyErr_Clear(); res = 0; }
        PyGILState_Release(gstate);
        return res == 1;
    }
    bool operator>=(const PyGenericWrapper& other) const {
        PyGILState_STATE gstate = PyGILState_Ensure();
        int res = PyObject_RichCompareBool(obj, other.obj, Py_GE);
        if (res == -1) { PyErr_Clear(); res = 0; }
        PyGILState_Release(gstate);
        return res == 1;
    }
    bool operator==(const PyGenericWrapper& other) const {
        PyGILState_STATE gstate = PyGILState_Ensure();
        int res = PyObject_RichCompareBool(obj, other.obj, Py_EQ);
        if (res == -1) { PyErr_Clear(); res = 0; }
        PyGILState_Release(gstate);
        return res == 1;
    }
};

} // namespace pybind
} // namespace algoat
