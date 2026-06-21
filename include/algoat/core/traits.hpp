#pragma once

#include <cstddef>
#include <ranges>

namespace algoat::core {

struct DataTraits {
    std::size_t size;
    double sortedness_ratio; // 0.0 = completely reversed, 1.0 = fully sorted
    bool has_duplicates;
};

template <std::ranges::random_access_range R>
DataTraits analyze(const R& data) {
    const std::size_t size = std::ranges::size(data);
    if (size <= 1) {
        return {size, 1.0, false};
    }

    std::size_t sorted_pairs = 0;
    bool has_duplicates = false;

    auto it = std::ranges::begin(data);
    auto prev = it;
    ++it;

    for (; it != std::ranges::end(data); ++it, ++prev) {
        if (*prev <= *it) {
            sorted_pairs++;
        }
        if (*prev == *it) {
            has_duplicates = true;
        }
    }

    // A fully sorted array has (size - 1) sorted pairs.
    double ratio = static_cast<double>(sorted_pairs) / static_cast<double>(size - 1);

    return {size, ratio, has_duplicates};
}

} // namespace algoat::core
