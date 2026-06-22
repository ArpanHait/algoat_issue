#pragma once

#include "algoat/core/traits.hpp"
#include "algoat/core/config.hpp"
#include "algoat/core/registry.hpp"
#include "algoat/sorting/sorting.hpp"
#include "algoat/searching/searching.hpp"
#include <string>
#include <span>
#include <stdexcept>
#include <optional>
#include <cstddef>
#include <utility>

#include <type_traits>

namespace algoat::core {

class Dispatcher {
    Registry<sorting::SortVariant> sort_registry_;
    Registry<searching::SearchVariant> search_registry_;
    AlgoConfig config_;

public:
    explicit Dispatcher(AlgoConfig config);

    template<typename T>
    void sort(std::span<T> data) const {
        DataTraits traits = analyze(data);
        std::string algo_name = config_.sorting.prefer.value_or("auto");
        
        if (algo_name == "auto" || algo_name.empty()) {
            if (traits.size < config_.sorting.small_threshold.value_or(32)) {
                algo_name = "insertionsort";
            } else if (traits.sortedness_ratio >= 0.9 || traits.sortedness_ratio <= 0.1) {
                algo_name = "timsort"; 
            } else {
                if constexpr (std::is_integral_v<T>) {
                    if (traits.size > 10000) {
                        algo_name = "radixsortlsd";
                    } else {
                        algo_name = "introsort";
                    }
                } else {
                    algo_name = "introsort";
                }
            }
        }

        if (!sort_registry_.has(algo_name)) {
            algo_name = config_.sorting.fallback.value_or("heapsort");
            if (!sort_registry_.has(algo_name)) {
                 throw std::runtime_error("Requested sorting algorithm not registered and fallback missing");
            }
        }

        auto algo_variant = sort_registry_.create(algo_name);
        std::visit([data](auto&& algo) {
            algo.sort(data);
        }, algo_variant);
    }

    template<typename T>
    std::optional<std::size_t> search(std::span<T> data, const T& target) const {
        DataTraits traits = analyze(data);
        std::string algo_name = config_.searching.prefer.value_or("auto");
        
        if (algo_name == "auto" || algo_name.empty()) {
            if (traits.sortedness_ratio == 1.0) {
                algo_name = "binarysearch";
            } else {
                algo_name = "linearsearch";
            }
        }

        if (!search_registry_.has(algo_name)) {
            algo_name = config_.searching.fallback.value_or("linearsearch");
            if (!search_registry_.has(algo_name)) {
                 throw std::runtime_error("Requested searching algorithm not registered and fallback missing");
            }
        }

        auto algo_variant = search_registry_.create(algo_name);
        return std::visit([data, &target](auto&& algo) -> std::optional<std::size_t> {
            return algo.search(data, target);
        }, algo_variant);
    }
};

} // namespace algoat::core
