#pragma once

#include <cstdint>
#include <span>
#include <cstring>
#include <algorithm>

namespace algoat::sorting {

inline void sort_boolean(std::span<uint8_t> data) noexcept {
    if (data.empty()) return;
    size_t count_false = 0;
    for (uint8_t val : data) {
        if (val == 0) {
            count_false++;
        }
    }
    
    size_t count_true = data.size() - count_false;
    if (count_false > 0) {
        std::memset(data.data(), 0, count_false);
    }
    if (count_true > 0) {
        std::memset(data.data() + count_false, 1, count_true);
    }
}

} // namespace algoat::sorting
