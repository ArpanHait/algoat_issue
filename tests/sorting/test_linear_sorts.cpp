#include <gtest/gtest.h>
#include "algoat/sorting/countingsort.hpp"
#include "algoat/sorting/pigeonholesort.hpp"
#include "algoat/sorting/radixsort.hpp"
#include "algoat/sorting/bucketsort.hpp"
#include <vector>
#include <algorithm>
#include <random>

using namespace algoat::sorting;

template <typename Algo>
class LinearSortTest : public ::testing::Test {
protected:
    Algo algo;
    void verify_sort(std::vector<int>& data) {
        auto expected = data;
        std::sort(expected.begin(), expected.end());
        algo.sort(std::span{data});
        EXPECT_EQ(data, expected);
    }
};

using LinearAlgos = ::testing::Types<CountingSort, PigeonholeSort, RadixSortLSD, RadixSortMSD, BucketSort>;
TYPED_TEST_SUITE(LinearSortTest, LinearAlgos);

TYPED_TEST(LinearSortTest, RandomData) {
    std::vector<int> data = {5, -3, 8, 1, -9, 2, 7};
    this->verify_sort(data);
}

TYPED_TEST(LinearSortTest, EmptyInput) {
    std::vector<int> data;
    this->verify_sort(data);
}

TYPED_TEST(LinearSortTest, SingleElement) {
    std::vector<int> data = {42};
    this->verify_sort(data);
}

TYPED_TEST(LinearSortTest, AllDuplicates) {
    std::vector<int> data = {7, 7, 7, 7, 7};
    this->verify_sort(data);
}

TYPED_TEST(LinearSortTest, AlreadySorted) {
    std::vector<int> data = {-5, -2, 0, 4, 5, 6, 7};
    this->verify_sort(data);
}

TYPED_TEST(LinearSortTest, ReverseSorted) {
    std::vector<int> data = {7, 6, 5, 4, 0, -2, -5};
    this->verify_sort(data);
}

TYPED_TEST(LinearSortTest, LargeRandom) {
    std::vector<int> data(1000);
    std::mt19937 gen(42);
    std::uniform_int_distribution<int> dist(-10000, 10000);
    for (int& x : data) {
        x = dist(gen);
    }
    this->verify_sort(data);
}
