#pragma once
#include <cstdint>

namespace algoat {

struct Rational {
    int64_t num;
    int64_t den;

    bool operator<(const Rational& other) const {
#if defined(__SIZEOF_INT128__)
        __int128 lhs = static_cast<__int128>(num) * other.den;
        __int128 rhs = static_cast<__int128>(other.num) * den;
        return lhs < rhs;
#else
        return num * other.den < other.num * den;
#endif
    }
    bool operator==(const Rational& other) const {
        return num * other.den == other.num * den;
    }
};

struct Vec3f {
    float x, y, z;
};

} // namespace algoat
