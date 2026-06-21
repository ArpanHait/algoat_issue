#pragma once

#include <concepts>
#include <string_view>
#include <span>
#include <optional>
#include <cstddef>
#include <variant>

#include "algoat/searching/linear_search.hpp"
#include "algoat/searching/binary_search.hpp"
#include "algoat/searching/interpolation_search.hpp"

namespace algoat::searching {

template<typename Algo, typename T>
concept SearchAlgorithm = requires(Algo algo, std::span<T> data, const T& target) {
    { algo.name() } -> std::convertible_to<std::string_view>;
    { algo.search(data, target) } -> std::same_as<std::optional<std::size_t>>;
    { algo.requires_sorted() } -> std::same_as<bool>;
};

using SearchVariant = std::variant<LinearSearch, BinarySearch, InterpolationSearch>;

} // namespace algoat::searching
