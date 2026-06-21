#include <benchmark/benchmark.h>
#include "algoat/sorting/insertionsort.hpp"
#include "algoat/sorting/quicksort.hpp"
#include "algoat/sorting/mergesort.hpp"
#include "algoat/sorting/heapsort.hpp"
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

static void BM_InsertionSort(benchmark::State& state) {
    auto data = generate_random_data(state.range(0));
    InsertionSort algo;
    for (auto _ : state) {
        state.PauseTiming();
        auto copy = data;
        state.ResumeTiming();
        algo.sort(std::span{copy});
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_InsertionSort)->RangeMultiplier(2)->Range(8, 8<<10)->Complexity();

static void BM_QuickSort(benchmark::State& state) {
    auto data = generate_random_data(state.range(0));
    QuickSort algo;
    for (auto _ : state) {
        state.PauseTiming();
        auto copy = data;
        state.ResumeTiming();
        algo.sort(std::span{copy});
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_QuickSort)->RangeMultiplier(2)->Range(8, 8<<10)->Complexity();

static void BM_MergeSort(benchmark::State& state) {
    auto data = generate_random_data(state.range(0));
    MergeSort algo;
    for (auto _ : state) {
        state.PauseTiming();
        auto copy = data;
        state.ResumeTiming();
        algo.sort(std::span{copy});
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MergeSort)->RangeMultiplier(2)->Range(8, 8<<10)->Complexity();

static void BM_HeapSort(benchmark::State& state) {
    auto data = generate_random_data(state.range(0));
    HeapSort algo;
    for (auto _ : state) {
        state.PauseTiming();
        auto copy = data;
        state.ResumeTiming();
        algo.sort(std::span{copy});
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_HeapSort)->RangeMultiplier(2)->Range(8, 8<<10)->Complexity();
