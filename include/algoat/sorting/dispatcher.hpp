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
                         const core::Config& config) {
        
        std::string algo_name = config.get_sorting_algorithm();
        
        // 1. Smart Fallbacks / Auto mode
        if (algo_name == "auto" || algo_name.empty()) {
            if (traits.size < 32) {
                algo_name = "insertionsort";
            } else if (traits.is_sorted || traits.is_reverse_sorted) {
                algo_name = "mergesort"; 
            } else {
                algo_name = "quicksort";
            }
        }

        // 2. Fallback if requested algo is missing
        if (!registry.has(algo_name)) {
            algo_name = "heapsort";
            if (!registry.has(algo_name)) {
                 throw std::runtime_error("Requested sorting algorithm not registered and heapsort fallback missing");
            }
        }

        SortVariant algo_variant = registry.create(algo_name);
        
        std::visit([data](auto&& algo) {
            algo.sort(data);
        }, algo_variant);
    }
};

} // namespace algoat::sorting
