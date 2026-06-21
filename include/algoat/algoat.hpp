#pragma once

#include "algoat/core/dispatcher.hpp"
#include "algoat/core/config.hpp"
#include <span>
#include <optional>
#include <cstddef>
#include <string>

namespace algoat {

// A global, default-configured dispatcher for convenience functions.
// For advanced usage, users can instantiate their own core::Dispatcher with a custom config.

inline core::AlgoConfig& get_global_config() {
    static core::AlgoConfig config;
    return config;
}

inline void load_global_config(const std::string& filepath) {
    get_global_config() = core::load_config(filepath);
}

template<typename T>
void sort(std::span<T> data) {
    core::Dispatcher dispatcher(get_global_config());
    dispatcher.sort(data);
}

template<typename T>
std::optional<std::size_t> search(std::span<T> data, const T& target) {
    core::Dispatcher dispatcher(get_global_config());
    return dispatcher.search(data, target);
}

} // namespace algoat
