#include "algoat/sorting/bitonicsort.hpp"
#include "algoat/sorting/bubblesort.hpp"
#include "algoat/sorting/combsort.hpp"
#include "algoat/sorting/cyclesort.hpp"
#include "algoat/sorting/gnomesort.hpp"
#include "algoat/sorting/selectionsort.hpp"
#include "algoat/sorting/shellsort.hpp"

#include <algorithm>
#include <gtest/gtest.h>
#include <random>
#include <vector>

using namespace algoat::sorting;

template <typename Algo> class ClassicalSortTest : public ::testing::Test {
protected:
    Algo algo;
    void verify_sort(std::vector<int>& data) {
        auto expected = data;
        std::sort(expected.begin(), expected.end());
        algo.sort(std::span{data});
        EXPECT_EQ(data, expected);
    }
};

using SortAlgos =
    ::testing::Types<SelectionSort, BubbleSort, ShellSort, CombSort, GnomeSort, CycleSort>;
TYPED_TEST_SUITE(ClassicalSortTest, SortAlgos);

TYPED_TEST(ClassicalSortTest, RandomData) {
    std::vector<int> data = {5, 3, 8, 1, 9, 2, 7};
    this->verify_sort(data);
}

TYPED_TEST(ClassicalSortTest, EmptyInput) {
    std::vector<int> data;
    this->verify_sort(data);
}

TYPED_TEST(ClassicalSortTest, SingleElement) {
    std::vector<int> data = {42};
    this->verify_sort(data);
}

TYPED_TEST(ClassicalSortTest, AllDuplicates) {
    std::vector<int> data = {7, 7, 7, 7, 7};
    this->verify_sort(data);
}

TYPED_TEST(ClassicalSortTest, AlreadySorted) {
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7};
    this->verify_sort(data);
}

TYPED_TEST(ClassicalSortTest, ReverseSorted) {
    std::vector<int> data = {7, 6, 5, 4, 3, 2, 1};
    this->verify_sort(data);
}

TYPED_TEST(ClassicalSortTest, LargeRandom) {
    std::vector<int> data(1000);
    std::mt19937 gen(42);
    std::uniform_int_distribution<int> dist(1, 10000);
    for (int& x : data) {
        x = dist(gen);
    }
    this->verify_sort(data);
}

class BitonicSortTest : public ::testing::Test {
protected:
    BitonicSort algo;
    void verify_sort(std::vector<int>& data) {
        auto expected = data;
        std::sort(expected.begin(), expected.end());
        algo.sort(std::span{data});
        EXPECT_EQ(data, expected);
    }
};

TEST_F(BitonicSortTest, RandomDataPowerOfTwo) {
    std::vector<int> data = {5, 3, 8, 1, 9, 2, 7, 4}; // Size 8
    verify_sort(data);
}

TEST_F(BitonicSortTest, EmptyInput) {
    std::vector<int> data;
    verify_sort(data);
}

TEST_F(BitonicSortTest, LargeRandomPowerOfTwo) {
    std::vector<int> data(1024);
    std::mt19937 gen(42);
    std::uniform_int_distribution<int> dist(1, 10000);
    for (int& x : data) {
        x = dist(gen);
    }
    verify_sort(data);
}

TEST_F(BitonicSortTest, ThrowsOnNonPowerOfTwo) {
    std::vector<int> data = {1, 2, 3};
    EXPECT_THROW(algo.sort(std::span{data}), std::invalid_argument);
}
