#include "algoat/sorting/insertionsort.hpp"

#include <algorithm>
#include <gtest/gtest.h>
#include <random>
#include <vector>

using namespace algoat::sorting;

class InsertionSortTest : public ::testing::Test {
protected:
    InsertionSort algo;

    void verify_sort(std::vector<int>& data) {
        auto expected = data;
        std::sort(expected.begin(), expected.end());
        algo.sort(std::span{data});
        EXPECT_EQ(data, expected);
    }
};

TEST_F(InsertionSortTest, RandomData) {
    std::vector<int> data = {5, 3, 8, 1, 9, 2, 7};
    verify_sort(data);
}

TEST_F(InsertionSortTest, EmptyInput) {
    std::vector<int> data;
    verify_sort(data);
}

TEST_F(InsertionSortTest, SingleElement) {
    std::vector<int> data = {42};
    verify_sort(data);
}

TEST_F(InsertionSortTest, AllDuplicates) {
    std::vector<int> data = {7, 7, 7, 7, 7};
    verify_sort(data);
}

TEST_F(InsertionSortTest, AlreadySorted) {
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7};
    verify_sort(data);
}

TEST_F(InsertionSortTest, ReverseSorted) {
    std::vector<int> data = {7, 6, 5, 4, 3, 2, 1};
    verify_sort(data);
}

TEST_F(InsertionSortTest, LargeRandom) {
    std::vector<int> data(1000);
    std::mt19937 gen(42);
    std::uniform_int_distribution<int> dist(1, 10000);
    for (int& x : data) {
        x = dist(gen);
    }
    verify_sort(data);
}
