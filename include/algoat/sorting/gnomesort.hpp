#pragma once

#include <string_view>
#include <span>
#include <concepts>
#include <algorithm>

namespace algoat::sorting {

struct GnomeSort {
    [[nodiscard]] constexpr std::string_view name() const noexcept {
        return "gnomesort";
    }

    [[nodiscard]] constexpr std::size_t preferred_min_size() const noexcept {
        return 0;
    }

    template<std::totally_ordered T>
    void sort(std::span<T> data) const {
        std::size_t pos = 1;
        std::size_t last = 1;
        
        while (pos < data.size()) {
            if (pos == 0 || data[pos - 1] <= data[pos]) {
                pos = last;
                last++;
            } else {
                std::swap(data[pos], data[pos - 1]);
                pos--;
            }
        }
    }
};

} // namespace algoat::sorting
