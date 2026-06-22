#include <gtest/gtest.h>
#include "algoat/sorting/introsort.hpp"
#include "algoat/sorting/timsort.hpp"
#include "algoat/sorting/blocksort.hpp"
#include <vector>
#include <algorithm>
#include <random>

using namespace algoat::sorting;

template <typename Algo>
class HybridSortTest : public ::testing::Test {
protected:
    Algo algo;
    void verify_sort(std::vector<int>& data) {
        auto expected = data;
        std::sort(expected.begin(), expected.end());
        algo.sort(std::span{data});
        EXPECT_EQ(data, expected);
    }
};

using HybridAlgos = ::testing::Types<IntroSort, TimSort, BlockSort>;
TYPED_TEST_SUITE(HybridSortTest, HybridAlgos);

TYPED_TEST(HybridSortTest, RandomData) {
    std::vector<int> data = {5, 3, 8, 1, 9, 2, 7};
    this->verify_sort(data);
}

TYPED_TEST(HybridSortTest, EmptyInput) {
    std::vector<int> data;
    this->verify_sort(data);
}

TYPED_TEST(HybridSortTest, SingleElement) {
    std::vector<int> data = {42};
    this->verify_sort(data);
}

TYPED_TEST(HybridSortTest, AllDuplicates) {
    std::vector<int> data = {7, 7, 7, 7, 7};
    this->verify_sort(data);
}

TYPED_TEST(HybridSortTest, AlreadySorted) {
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7};
    this->verify_sort(data);
}

TYPED_TEST(HybridSortTest, ReverseSorted) {
    std::vector<int> data = {7, 6, 5, 4, 3, 2, 1};
    this->verify_sort(data);
}

TYPED_TEST(HybridSortTest, LargeRandom) {
    std::vector<int> data(2000);
    std::mt19937 gen(42);
    std::uniform_int_distribution<int> dist(1, 10000);
    for (int& x : data) {
        x = dist(gen);
    }
    this->verify_sort(data);
}
