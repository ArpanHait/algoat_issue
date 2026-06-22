#include <benchmark/benchmark.h>
#include "algoat/sorting/insertionsort.hpp"
#include "algoat/sorting/quicksort.hpp"
#include "algoat/sorting/mergesort.hpp"
#include "algoat/sorting/heapsort.hpp"
#include "algoat/sorting/timsort.hpp"
#include "algoat/sorting/introsort.hpp"
#include "algoat/sorting/blocksort.hpp"
#include "algoat/sorting/radixsort.hpp"
#include "algoat/sorting/countingsort.hpp"
#include "algoat/sorting/bucketsort.hpp"
#include "algoat/sorting/shellsort.hpp"
#include "algoat/sorting/combsort.hpp"
#include <vector>
#include <random>
#include <algorithm>

using namespace algoat::sorting;

static std::vector<int> generate_random_data(size_t size) {
    std::vector<int> data(size);
    std::mt19937 gen(42);
    std::uniform_int_distribution<int> dist(1, 1000000);
    for (size_t i = 0; i < size; ++i) {
        data[i] = dist(gen);
    }
    return data;
}

static void BM_StdSort(benchmark::State& state) {
    auto data = generate_random_data(state.range(0));
    for (auto _ : state) {
        state.PauseTiming();
        auto copy = data;
        state.ResumeTiming();
        std::sort(copy.begin(), copy.end());
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_StdSort)->RangeMultiplier(2)->Range(8, 8<<12)->Complexity();

#define DECLARE_SORT_BENCHMARK(AlgoClass) \
    static void BM_##AlgoClass(benchmark::State& state) { \
        auto data = generate_random_data(state.range(0)); \
        AlgoClass algo; \
        for (auto _ : state) { \
            state.PauseTiming(); \
            auto copy = data; \
            state.ResumeTiming(); \
            algo.sort(std::span{copy}); \
        } \
        state.SetComplexityN(state.range(0)); \
    } \
    BENCHMARK(BM_##AlgoClass)->RangeMultiplier(2)->Range(8, 8<<12)->Complexity();

DECLARE_SORT_BENCHMARK(InsertionSort)
DECLARE_SORT_BENCHMARK(QuickSort)
DECLARE_SORT_BENCHMARK(MergeSort)
DECLARE_SORT_BENCHMARK(HeapSort)
DECLARE_SORT_BENCHMARK(TimSort)
DECLARE_SORT_BENCHMARK(IntroSort)
DECLARE_SORT_BENCHMARK(BlockSort)
DECLARE_SORT_BENCHMARK(RadixSortLSD)
DECLARE_SORT_BENCHMARK(RadixSortMSD)
DECLARE_SORT_BENCHMARK(CountingSort)
DECLARE_SORT_BENCHMARK(BucketSort)
DECLARE_SORT_BENCHMARK(ShellSort)
DECLARE_SORT_BENCHMARK(CombSort)
