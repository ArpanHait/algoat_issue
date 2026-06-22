#pragma once

#include <string_view>
#include <span>
#include <concepts>
#include <algorithm>

namespace algoat::sorting {

struct SelectionSort {
    [[nodiscard]] constexpr std::string_view name() const noexcept {
        return "selectionsort";
    }

    [[nodiscard]] constexpr std::size_t preferred_min_size() const noexcept {
        return 0;
    }

    template<std::totally_ordered T>
    void sort(std::span<T> data) const {
        for (auto it = data.begin(); it != data.end(); ++it) {
            auto min_it = std::min_element(it, data.end());
            if (min_it != it) {
                std::iter_swap(it, min_it);
            }
        }
    }
};

} // namespace algoat::sorting
