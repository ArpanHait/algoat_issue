#include "algoat/core/dispatcher.hpp"
#include "algoat/sorting/insertionsort.hpp"
#include "algoat/sorting/quicksort.hpp"
#include "algoat/sorting/mergesort.hpp"
#include "algoat/sorting/heapsort.hpp"
#include "algoat/searching/linear_search.hpp"
#include "algoat/searching/binary_search.hpp"
#include "algoat/searching/interpolation_search.hpp"

#include "algoat/sorting/selectionsort.hpp"
#include "algoat/sorting/bubblesort.hpp"
#include "algoat/sorting/shellsort.hpp"

namespace algoat::core {

Dispatcher::Dispatcher(AlgoConfig config) : config_(std::move(config)) {
    // Register sorting
    sort_registry_.register_algo("insertionsort", []() -> sorting::SortVariant { return sorting::InsertionSort{}; });
    sort_registry_.register_algo("quicksort", []() -> sorting::SortVariant { return sorting::QuickSort{}; });
    sort_registry_.register_algo("mergesort", []() -> sorting::SortVariant { return sorting::MergeSort{}; });
    sort_registry_.register_algo("heapsort", []() -> sorting::SortVariant { return sorting::HeapSort{}; });
    sort_registry_.register_algo("selectionsort", []() -> sorting::SortVariant { return sorting::SelectionSort{}; });
    sort_registry_.register_algo("bubblesort", []() -> sorting::SortVariant { return sorting::BubbleSort{}; });
    sort_registry_.register_algo("shellsort", []() -> sorting::SortVariant { return sorting::ShellSort{}; });

    // Register searching
    search_registry_.register_algo("linearsearch", []() -> searching::SearchVariant { return searching::LinearSearch{}; });
    search_registry_.register_algo("binarysearch", []() -> searching::SearchVariant { return searching::BinarySearch{}; });
    search_registry_.register_algo("interpolationsearch", []() -> searching::SearchVariant { return searching::InterpolationSearch{}; });
}

} // namespace algoat::core
