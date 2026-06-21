#pragma once

#include <string_view>
#include <span>
#include <optional>
#include <cstddef>
#include <type_traits>

namespace algoat::searching {

struct InterpolationSearch {
    [[nodiscard]] constexpr std::string_view name() const noexcept {
        return "interpolationsearch";
    }

    template<typename T>
    std::optional<std::size_t> search(std::span<T> data, const T& target) const {
        if (data.empty()) return std::nullopt;

        if constexpr (std::is_arithmetic_v<T>) {
            std::size_t low = 0;
            std::size_t high = data.size() - 1;

            while (low <= high && target >= data[low] && target <= data[high]) {
                if (low == high) {
                    if (data[low] == target) return low;
                    return std::nullopt;
                }

                if (data[high] == data[low]) {
                    if (data[low] == target) return low;
                    return std::nullopt;
                }

                double pos_double = static_cast<double>(low) + 
                    ((static_cast<double>(high) - static_cast<double>(low)) / 
                     (static_cast<double>(data[high]) - static_cast<double>(data[low]))) * 
                    (static_cast<double>(target) - static_cast<double>(data[low]));
                
                std::size_t pos = static_cast<std::size_t>(pos_double);

                if (data[pos] == target) {
                    return pos;
                }

                if (data[pos] < target) {
                    low = pos + 1;
                } else {
                    if (pos == 0) break;
                    high = pos - 1;
                }
            }
        } else {
            // Fallback for non-arithmetic types
            std::size_t left = 0;
            std::size_t right = data.size() - 1;
            while (left <= right) {
                std::size_t mid = left + (right - left) / 2;
                if (data[mid] == target) return mid;
                if (data[mid] < target) left = mid + 1;
                else {
                    if (mid == 0) break;
                    right = mid - 1;
                }
            }
        }

        return std::nullopt;
    }

    [[nodiscard]] constexpr bool requires_sorted() const noexcept {
        return true;
    }
};

} // namespace algoat::searching
