#pragma once

#include <string_view>
#include <span>
#include <concepts>
#include <utility>

namespace algoat::sorting {

struct BubbleSort {
    [[nodiscard]] constexpr std::string_view name() const noexcept {
        return "bubblesort";
    }

    [[nodiscard]] constexpr std::size_t preferred_min_size() const noexcept {
        return 0;
    }

    template<std::totally_ordered T>
    void sort(std::span<T> data) const {
        if (data.empty()) return;
        bool swapped = true;
        for (std::size_t i = 0; i < data.size() - 1 && swapped; ++i) {
            swapped = false;
            for (std::size_t j = 0; j < data.size() - i - 1; ++j) {
                if (data[j + 1] < data[j]) {
                    std::swap(data[j], data[j + 1]);
                    swapped = true;
                }
            }
        }
    }
};

} // namespace algoat::sorting
