#pragma once

#include <string_view>
#include <span>
#include <concepts>
#include <algorithm>
#include <bit>
#include "algoat/sorting/insertionsort.hpp"
#include "algoat/sorting/heapsort.hpp"

namespace algoat::sorting {

struct IntroSort {
    [[nodiscard]] constexpr std::string_view name() const noexcept {
        return "introsort";
    }

    [[nodiscard]] constexpr std::size_t preferred_min_size() const noexcept {
        return 0;
    }

    template<std::totally_ordered T>
    static T get_pivot(const T& a, const T& b, const T& c) {
        // Branchless median-of-three. 
        // std::min and std::max typically compile down to CMOV (Conditional Move)
        // instructions on x86 or CSEL on ARM, entirely avoiding branch misprediction penalties.
        return std::max(std::min(a, b), std::min(std::max(a, b), c));
    }

    template<std::totally_ordered T>
    static void introsort_impl(std::span<T> data, int depth_limit) {
        if (data.size() <= 32) {
            InsertionSort{}.sort(data);
            return;
        }

        if (depth_limit == 0) {
            HeapSort{}.sort(data);
            return;
        }

        // Median-of-three pivot selection
        auto pivot = get_pivot(data[0], data[data.size() / 2], data[data.size() - 1]);
        
        // Hoare partition scheme
        auto* left = data.data() - 1;
        auto* right = data.data() + data.size();
        
        while (true) {
            do { left++; } while (*left < pivot);
            do { right--; } while (pivot < *right);
            if (left >= right) break;
            std::swap(*left, *right);
        }
        
        std::size_t pivot_idx = right - data.data() + 1;

        introsort_impl(data.subspan(0, pivot_idx), depth_limit - 1);
        introsort_impl(data.subspan(pivot_idx, data.size() - pivot_idx), depth_limit - 1);
    }

    template<std::totally_ordered T>
    void sort(std::span<T> data) const {
        if (data.empty()) return;
        int depth_limit = 2 * std::bit_width(data.size());
        introsort_impl(data, depth_limit);
    }
};

} // namespace algoat::sorting
