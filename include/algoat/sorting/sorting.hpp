#pragma once

#include <concepts>
#include <string_view>
#include <span>
#include <cstddef>
#include <variant>

#include "algoat/sorting/insertionsort.hpp"
#include "algoat/sorting/quicksort.hpp"
#include "algoat/sorting/mergesort.hpp"
#include "algoat/sorting/heapsort.hpp"
#include "algoat/sorting/selectionsort.hpp"
#include "algoat/sorting/bubblesort.hpp"
#include "algoat/sorting/shellsort.hpp"
#include "algoat/sorting/combsort.hpp"
#include "algoat/sorting/gnomesort.hpp"

namespace algoat::sorting {

template<typename Algo, typename T>
concept SortAlgorithm = requires(Algo algo, std::span<T> data) {
    { algo.name() } -> std::convertible_to<std::string_view>;
    { algo.sort(data) } -> std::same_as<void>;
    { algo.preferred_min_size() } -> std::convertible_to<std::size_t>;
};

using SortVariant = std::variant<InsertionSort, QuickSort, MergeSort, HeapSort, SelectionSort, BubbleSort, ShellSort, CombSort, GnomeSort>;

} // namespace algoat::sorting
