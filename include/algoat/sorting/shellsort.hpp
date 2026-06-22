#pragma once

#include <string_view>
#include <span>
#include <concepts>
#include <utility>
#include <iterator>

namespace algoat::sorting {

struct ShellSort {
    [[nodiscard]] constexpr std::string_view name() const noexcept {
        return "shellsort";
    }

    [[nodiscard]] constexpr std::size_t preferred_min_size() const noexcept {
        return 0;
    }

    template<std::totally_ordered T>
    void sort(std::span<T> data) const {
        if (data.size() <= 1) return;

        constexpr std::size_t gaps[] = {
            1, 4, 10, 23, 57, 132, 301, 701, 1577, 3548, 7983, 17961, 
            40412, 90927, 204585, 460316, 1035711, 2330350, 5243287, 
            11797395, 26544138, 59724310, 134379697, 302354318, 680297215
        };
        
        int gap_idx = std::size(gaps) - 1;
        while (gap_idx >= 0 && gaps[gap_idx] >= data.size()) {
            gap_idx--;
        }

        for (; gap_idx >= 0; gap_idx--) {
            std::size_t g = gaps[gap_idx];
            for (std::size_t i = g; i < data.size(); ++i) {
                T temp = std::move(data[i]);
                std::size_t j = i;
                while (j >= g && temp < data[j - g]) {
                    data[j] = std::move(data[j - g]);
                    j -= g;
                }
                data[j] = std::move(temp);
            }
        }
    }
};

} // namespace algoat::sorting
