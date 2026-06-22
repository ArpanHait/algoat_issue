#pragma once

#include <string_view>
#include <span>
#include <concepts>
#include <algorithm>
#include <cassert>
#include <bit>
#include <stdexcept>

namespace algoat::sorting {

struct BitonicSort {
    [[nodiscard]] constexpr std::string_view name() const noexcept {
        return "bitonicsort";
    }

    [[nodiscard]] constexpr std::size_t preferred_min_size() const noexcept {
        return 0;
    }

    template<std::totally_ordered T>
    static void bitonic_merge(std::span<T> a, bool dir) {
        if (a.size() > 1) {
            std::size_t k = a.size() / 2;
            for (std::size_t i = 0; i < k; ++i) {
                if (dir == (a[i] > a[i + k])) {
                    std::swap(a[i], a[i + k]);
                }
            }
            bitonic_merge(a.subspan(0, k), dir);
            bitonic_merge(a.subspan(k, k), dir);
        }
    }

    template<std::totally_ordered T>
    static void bitonic_sort_impl(std::span<T> a, bool dir) {
        if (a.size() > 1) {
            std::size_t k = a.size() / 2;
            bitonic_sort_impl(a.subspan(0, k), true);
            bitonic_sort_impl(a.subspan(k, k), false);
            bitonic_merge(a, dir);
        }
    }

    template<std::totally_ordered T>
    void sort(std::span<T> data) const {
        if (data.empty()) return;
        if (!std::has_single_bit(data.size())) {
            throw std::invalid_argument("Bitonic sort requires array size to be a power of 2");
        }
        bitonic_sort_impl(data, true);
    }
};

} // namespace algoat::sorting
