#pragma once

#include <string_view>
#include <span>
#include <cstddef>
#include <utility>

namespace algoat::sorting {

struct InsertionSort {
    [[nodiscard]] constexpr std::string_view name() const noexcept {
        return "insertionsort";
    }

    template<typename T>
    void sort(std::span<T> data) const {
        const std::size_t n = data.size();
        for (std::size_t i = 1; i < n; ++i) {
            T key = std::move(data[i]);
            std::size_t j = i;
            while (j > 0 && data[j - 1] > key) {
                data[j] = std::move(data[j - 1]);
                --j;
            }
            data[j] = std::move(key);
        }
    }

    [[nodiscard]] constexpr std::size_t preferred_min_size() const noexcept {
        return 0;
    }
};

} // namespace algoat::sorting
