#pragma once

#include <string>
#include <optional>
#include <cstddef>

namespace algoat::core {

struct SortingConfig {
    std::optional<std::string> prefer;
    std::optional<std::string> fallback;
    std::optional<std::size_t> small_threshold;
};

struct SearchingConfig {
    std::optional<std::string> prefer;
    std::optional<std::string> fallback;
};

struct AlgoConfig {
    SortingConfig sorting;
    SearchingConfig searching;
};

AlgoConfig load_config(const std::string& filepath);

} // namespace algoat::core
