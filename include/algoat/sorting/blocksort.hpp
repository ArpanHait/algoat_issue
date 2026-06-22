#pragma once

#include <string_view>
#include <span>
#include <concepts>
#include <algorithm>
#include <cmath>
#include "algoat/sorting/insertionsort.hpp"

namespace algoat::sorting {

struct BlockSort {
    [[nodiscard]] constexpr std::string_view name() const noexcept {
        return "blocksort";
    }

    [[nodiscard]] constexpr std::size_t preferred_min_size() const noexcept {
        return 0;
    }

    template<std::totally_ordered T>
    void sort(std::span<T> data) const {
        if (data.empty()) return;
        
        std::size_t n = data.size();
        std::size_t block_size = static_cast<std::size_t>(std::sqrt(n));
        
        if (block_size < 16) {
            InsertionSort{}.sort(data);
            return;
        }

        for (std::size_t i = 0; i < n; i += block_size) {
            std::size_t end = std::min(i + block_size, n);
            std::sort(data.begin() + i, data.begin() + end);
        }

        for (std::size_t size = block_size; size < n; size = 2 * size) {
            for (std::size_t left = 0; left < n; left += 2 * size) {
                std::size_t mid = std::min(left + size, n);
                std::size_t right = std::min(left + 2 * size, n);
                if (mid < right) {
                    std::inplace_merge(data.begin() + left, data.begin() + mid, data.begin() + right);
                }
            }
        }
    }
};

} // namespace algoat::sorting
