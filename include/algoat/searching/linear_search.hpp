#pragma once

#include <string_view>
#include <span>
#include <optional>
#include <cstddef>

namespace algoat::searching {

struct LinearSearch {
    [[nodiscard]] constexpr std::string_view name() const noexcept {
        return "linearsearch";
    }

    template<typename T>
    std::optional<std::size_t> search(std::span<T> data, const T& target) const {
        for (std::size_t i = 0; i < data.size(); ++i) {
            if (data[i] == target) {
                return i; // returns first match
            }
        }
        return std::nullopt;
    }

    [[nodiscard]] constexpr bool requires_sorted() const noexcept {
        return false;
    }
};

} // namespace algoat::searching
