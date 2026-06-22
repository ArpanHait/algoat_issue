#pragma once

#include <string_view>
#include <span>
#include <concepts>
#include <algorithm>
#include <utility>

namespace algoat::sorting {

struct CycleSort {
    [[nodiscard]] constexpr std::string_view name() const noexcept {
        return "cyclesort";
    }

    [[nodiscard]] constexpr std::size_t preferred_min_size() const noexcept {
        return 0;
    }

    template<std::totally_ordered T>
    void sort(std::span<T> data) const {
        if (data.size() <= 1) return;

        for (std::size_t cycle_start = 0; cycle_start < data.size() - 1; ++cycle_start) {
            T item = std::move(data[cycle_start]);
            
            std::size_t pos = cycle_start;
            for (std::size_t i = cycle_start + 1; i < data.size(); ++i) {
                if (data[i] < item) {
                    pos++;
                }
            }

            if (pos == cycle_start) {
                continue; 
            }

            while (item == data[pos]) {
                pos++;
            }

            if (pos != cycle_start) {
                std::swap(item, data[pos]);
            }

            while (pos != cycle_start) {
                pos = cycle_start;
                for (std::size_t i = cycle_start + 1; i < data.size(); ++i) {
                    if (data[i] < item) {
                        pos++;
                    }
                }
                while (item == data[pos]) {
                    pos++;
                }
                if (item != data[pos]) {
                    std::swap(item, data[pos]);
                }
            }
        }
    }
};

} // namespace algoat::sorting
