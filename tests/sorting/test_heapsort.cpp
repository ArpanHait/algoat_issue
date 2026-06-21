#include <gtest/gtest.h>
#include "algoat/sorting/heapsort.hpp"
#include <vector>
#include <algorithm>
#include <random>

using namespace algoat::sorting;

class HeapSortTest : public ::testing::Test {
protected:
    HeapSort algo;

    void verify_sort(std::vector<int>& data) {
        auto expected = data;
        std::sort(expected.begin(), expected.end());
        algo.sort(std::span{data});
        EXPECT_EQ(data, expected);
    }
};

TEST_F(HeapSortTest, RandomData) {
    std::vector<int> data = {5, 3, 8, 1, 9, 2, 7};
    verify_sort(data);
}

TEST_F(HeapSortTest, EmptyInput) {
    std::vector<int> data;
    verify_sort(data);
}

TEST_F(HeapSortTest, SingleElement) {
    std::vector<int> data = {42};
    verify_sort(data);
}

TEST_F(HeapSortTest, AllDuplicates) {
    std::vector<int> data = {7, 7, 7, 7, 7};
    verify_sort(data);
}

TEST_F(HeapSortTest, AlreadySorted) {
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7};
    verify_sort(data);
}

TEST_F(HeapSortTest, ReverseSorted) {
    std::vector<int> data = {7, 6, 5, 4, 3, 2, 1};
    verify_sort(data);
}

TEST_F(HeapSortTest, LargeRandom) {
    std::vector<int> data(1000);
    std::mt19937 gen(42);
    std::uniform_int_distribution<int> dist(1, 10000);
    for (int& x : data) {
        x = dist(gen);
    }
    verify_sort(data);
}
