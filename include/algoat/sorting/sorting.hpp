#pragma once

#include <concepts>
#include <string_view>
#include <span>
#include <cstddef>
#include <variant>

#include "algoat/sorting/insertionsort.hpp"
#include "algoat/sorting/quicksort.hpp"

namespace algoat::sorting {

template<typename Algo, typename T>
concept SortAlgorithm = requires(Algo algo, std::span<T> data) {
    { algo.name() } -> std::convertible_to<std::string_view>;
    { algo.sort(data) } -> std::same_as<void>;
    { algo.preferred_min_size() } -> std::convertible_to<std::size_t>;
};

using SortVariant = std::variant<InsertionSort, QuickSort>;

} // namespace algoat::sorting
