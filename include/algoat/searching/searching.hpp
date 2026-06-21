#pragma once

#include <concepts>
#include <string_view>
#include <span>
#include <optional>
#include <cstddef>
#include <variant>

namespace algoat::searching {

template<typename Algo, typename T>
concept SearchAlgorithm = requires(Algo algo, std::span<T> data, const T& target) {
    { algo.name() } -> std::convertible_to<std::string_view>;
    { algo.search(data, target) } -> std::same_as<std::optional<std::size_t>>;
    { algo.requires_sorted() } -> std::same_as<bool>;
};

using SearchVariant = std::variant<std::monostate>;

} // namespace algoat::searching
