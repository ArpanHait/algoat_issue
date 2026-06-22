#pragma once

#include <string_view>
#include <span>
#include <concepts>
#include <algorithm>

namespace algoat::sorting {

struct CombSort {
    [[nodiscard]] constexpr std::string_view name() const noexcept {
        return "combsort";
    }

    [[nodiscard]] constexpr std::size_t preferred_min_size() const noexcept {
        return 0;
    }

    template<std::totally_ordered T>
    void sort(std::span<T> data) const {
        std::size_t gap = data.size();
        bool swapped = true;
        
        while (gap > 1 || swapped) {
            gap = (gap * 10) / 13; // Shrink factor 1.3
            if (gap < 1) gap = 1;
            
            swapped = false;
            for (std::size_t i = 0; i + gap < data.size(); ++i) {
                if (data[i + gap] < data[i]) {
                    std::swap(data[i], data[i + gap]);
                    swapped = true;
                }
            }
        }
    }
};

} // namespace algoat::sorting
