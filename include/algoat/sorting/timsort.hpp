#pragma once

#include <string_view>
#include <span>
#include <concepts>
#include <algorithm>
#include "algoat/sorting/insertionsort.hpp"

namespace algoat::sorting {

struct TimSort {
    [[nodiscard]] constexpr std::string_view name() const noexcept {
        return "timsort";
    }

    [[nodiscard]] constexpr std::size_t preferred_min_size() const noexcept {
        return 0;
    }

    static constexpr std::size_t RUN_SIZE = 32;

    template<std::totally_ordered T>
    void sort(std::span<T> data) const {
        if (data.empty()) return;
        
        std::size_t n = data.size();

        // 1. Sort individual runs
        for (std::size_t i = 0; i < n; i += RUN_SIZE) {
            std::size_t end = std::min(i + RUN_SIZE, n);
            InsertionSort{}.sort(data.subspan(i, end - i));
        }

        // 2. Merge runs
        for (std::size_t size = RUN_SIZE; size < n; size = 2 * size) {
            for (std::size_t left = 0; left < n; left += 2 * size) {
                std::size_t mid = std::min(left + size, n);
                std::size_t right = std::min(left + 2 * size, n);

                if (mid < right) {
                    std::inplace_merge(
                        data.begin() + left,
                        data.begin() + mid,
                        data.begin() + right
                    );
                }
            }
        }
    }
};

} // namespace algoat::sorting
