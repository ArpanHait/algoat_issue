#pragma once

#include <string_view>
#include <span>
#include <optional>
#include <cstddef>

namespace algoat::searching {

struct BinarySearch {
    [[nodiscard]] constexpr std::string_view name() const noexcept {
        return "binarysearch";
    }

    template<typename T>
    std::optional<std::size_t> search(std::span<T> data, const T& target) const {
        if (data.empty()) return std::nullopt;

        std::size_t left = 0;
        std::size_t right = data.size() - 1;

        while (left <= right) {
            std::size_t mid = left + (right - left) / 2;
            if (data[mid] == target) {
                return mid;
            } else if (data[mid] < target) {
                left = mid + 1;
            } else {
                if (mid == 0) break;
                right = mid - 1;
            }
        }
        return std::nullopt;
    }

    [[nodiscard]] constexpr bool requires_sorted() const noexcept {
        return true;
    }
};

} // namespace algoat::searching
