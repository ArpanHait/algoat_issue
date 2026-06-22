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
    static void introsort_impl(std::span<T> data, int depth_limit) {
        if (data.size() <= 16) {
            InsertionSort{}.sort(data);
            return;
        }

        if (depth_limit == 0) {
            HeapSort{}.sort(data);
            return;
        }

        auto pivot = data[data.size() / 2];
        auto* left = data.data();
        auto* right = data.data() + data.size() - 1;
        while (left <= right) {
            while (*left < pivot) left++;
            while (pivot < *right) right--;
            if (left <= right) {
                std::swap(*left, *right);
                left++;
                right--;
            }
        }
        
        std::size_t left_size = left - data.data();
        std::size_t right_size = data.size() - left_size;

        if (left_size > 0) {
            introsort_impl(data.subspan(0, left_size), depth_limit - 1);
        }
        if (right_size > 0) {
            introsort_impl(data.subspan(left_size, right_size), depth_limit - 1);
        }
    }

    template<std::totally_ordered T>
    void sort(std::span<T> data) const {
        if (data.empty()) return;
        int depth_limit = 2 * std::bit_width(data.size());
        introsort_impl(data, depth_limit);
    }
};

} // namespace algoat::sorting
