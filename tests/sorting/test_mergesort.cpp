#include "algoat/sorting/mergesort.hpp"

#include <algorithm>
#include <gtest/gtest.h>
#include <random>
#include <vector>

using namespace algoat::sorting;

class MergeSortTest : public ::testing::Test {
protected:
    MergeSort algo;

    void verify_sort(std::vector<int>& data) {
        auto expected = data;
        std::sort(expected.begin(), expected.end());
        algo.sort(std::span{data});
        EXPECT_EQ(data, expected);
    }
};

TEST_F(MergeSortTest, RandomData) {
    std::vector<int> data = {5, 3, 8, 1, 9, 2, 7};
    verify_sort(data);
}

TEST_F(MergeSortTest, EmptyInput) {
    std::vector<int> data;
    verify_sort(data);
}

TEST_F(MergeSortTest, SingleElement) {
    std::vector<int> data = {42};
    verify_sort(data);
}

TEST_F(MergeSortTest, AllDuplicates) {
    std::vector<int> data = {7, 7, 7, 7, 7};
    verify_sort(data);
}

TEST_F(MergeSortTest, AlreadySorted) {
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7};
    verify_sort(data);
}

TEST_F(MergeSortTest, ReverseSorted) {
    std::vector<int> data = {7, 6, 5, 4, 3, 2, 1};
    verify_sort(data);
}

TEST_F(MergeSortTest, LargeRandom) {
    std::vector<int> data(1000);
    std::mt19937 gen(42);
    std::uniform_int_distribution<int> dist(1, 10000);
    for (int& x : data) {
        x = dist(gen);
    }
    verify_sort(data);
}

struct StableItem {
    int key = 0;
    int original_index = 0;

    bool operator<=(const StableItem& other) const {
        return key <= other.key;
    }
    bool operator<(const StableItem& other) const {
        return key < other.key;
    }
    bool operator==(const StableItem& other) const {
        return key == other.key;
    }
    bool operator>(const StableItem& other) const {
        return key > other.key;
    }
};

TEST_F(MergeSortTest, IsStable) {
    std::vector<StableItem> data = {{3, 0}, {1, 1}, {3, 2}, {2, 3}, {1, 4}, {3, 5}};

    algo.sort(std::span{data});

    // Check keys are sorted
    EXPECT_EQ(data[0].key, 1);
    EXPECT_EQ(data[1].key, 1);
    EXPECT_EQ(data[2].key, 2);
    EXPECT_EQ(data[3].key, 3);
    EXPECT_EQ(data[4].key, 3);
    EXPECT_EQ(data[5].key, 3);

    // Check stable order
    EXPECT_EQ(data[0].original_index, 1);
    EXPECT_EQ(data[1].original_index, 4);
    EXPECT_EQ(data[2].original_index, 3);
    EXPECT_EQ(data[3].original_index, 0);
    EXPECT_EQ(data[4].original_index, 2);
    EXPECT_EQ(data[5].original_index, 5);
}
