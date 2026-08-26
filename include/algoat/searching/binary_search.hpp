/**
 * @file binary_search.hpp
 * @brief Binary Search algorithm implementation.
 */

#pragma once

#include <cstddef>
#include <optional>
#include <span>
#include <string_view>

namespace algoat::searching {

/**
 * @struct BinarySearch
 * @brief Logarithmic search on sorted spans using midpoint bisection.
 *
 * @par Characteristics:
 * - <b>Preconditions:</b> Range must be sorted in ascending order.
 *
 * @par Time Complexity:
 * - Best Case: @c O(1) (target is at midpoint)
 * - Average Case: @c O(log N)
 * - Worst Case: @c O(log N)
 *
 * @par Space Complexity:
 * - Auxiliary Space: @c O(1) auxiliary space
 */
struct BinarySearch {
    /**
     * @brief Returns the unique identifier for this algorithm.
     * @return "binarysearch"
     */
    [[nodiscard]] static constexpr std::string_view name() noexcept {
        return "binarysearch";
    }

    /**
     * @brief Searches for target using binary search with overflow-safe midpoint calculation.
     * @tparam T Element type supporting <tt>operator==</tt> and <tt>operator<</tt>.
     *
     * @param data Sorted span of elements.
     *
     * @param target Value to locate.
     * @return Index of a matching element if present, or @c std::nullopt.
     */
    template <typename T>
    std::optional<std::size_t> search(std::span<T> data, const T& target) const {
        return search(std::span<const T>{data.data(), data.size()}, target);
    }

    template <typename T>
    std::optional<std::size_t> search(std::span<const T> data, const T& target) const {
        if (data.empty()) {
            return std::nullopt;
        }

        const T* base = data.data();
        std::size_t range_length = data.size();

        while (range_length > 1) {
            std::size_t half = range_length / 2;
            base = (base[half] < target) ? (base + half) : base;
            range_length -= half;
        }

        std::size_t index = static_cast<std::size_t>(base - data.data());
        if (*base == target) {
            return index;
        }
        if (index + 1 < data.size() && *(base + 1) == target) {
            return index + 1;
        }

        return std::nullopt;
    }

    /**
     * @brief Indicates whether this search algorithm requires sorted input.
     * @return @c true
     */
    [[nodiscard]] static constexpr bool requires_sorted() noexcept {
        return true;
    }
};

} // namespace algoat::searching
