#pragma once

#include "algoat/core/traits.hpp"
#include "algoat/core/config.hpp"
#include "algoat/core/registry.hpp"
#include "algoat/sorting/sorting.hpp"
#include <string>
#include <span>
#include <stdexcept>
#include <variant>

namespace algoat::sorting {

struct SortingDispatcher {
    template<typename T>
    static void dispatch(std::span<T> data, 
                         const core::Registry<SortVariant>& registry,
                         const core::DataTraits& traits,
                         const core::AlgoConfig& config) {
        
        std::string algo_name = config.sorting.prefer.value_or("auto");
        
        // 1. Smart Fallbacks / Auto mode
        if (algo_name == "auto" || algo_name.empty()) {
            if (traits.size < config.sorting.small_threshold.value_or(32)) {
                algo_name = "insertionsort";
            } else if (traits.sortedness_ratio >= 0.9 || traits.sortedness_ratio <= 0.1) {
                algo_name = "mergesort"; 
            } else {
                algo_name = "quicksort";
            }
        }

        // 2. Fallback if requested algo is missing
        if (!registry.has(algo_name)) {
            algo_name = config.sorting.fallback.value_or("heapsort");
            if (!registry.has(algo_name)) {
                 throw std::runtime_error("Requested sorting algorithm not registered and fallback missing");
            }
        }

        SortVariant algo_variant = registry.create(algo_name);
        
        std::visit([data](auto&& algo) {
            algo.sort(data);
        }, algo_variant);
    }
};

} // namespace algoat::sorting
