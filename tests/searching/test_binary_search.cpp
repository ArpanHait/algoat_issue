#include "algoat/searching/binary_search.hpp"

#include <gtest/gtest.h>
#include <vector>

using namespace algoat::searching;

class BinarySearchTest : public ::testing::Test {
protected:
    BinarySearch algo;
};

TEST_F(BinarySearchTest, FoundMiddle) {
    std::vector<int> data = {1, 2, 3, 5, 7, 8, 9};
    auto result = algo.search(std::span{data}, 5);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), 3);
}

TEST_F(BinarySearchTest, NotFound) {
    std::vector<int> data = {1, 2, 3, 5, 7, 8, 9};
    auto result = algo.search(std::span{data}, 42);
    EXPECT_FALSE(result.has_value());
}

TEST_F(BinarySearchTest, EmptyInput) {
    std::vector<int> data;
    auto result = algo.search(std::span{data}, 1);
    EXPECT_FALSE(result.has_value());
}

TEST_F(BinarySearchTest, FoundFirst) {
    std::vector<int> data = {1, 2, 3, 5, 7, 8, 9};
    auto result = algo.search(std::span{data}, 1);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), 0);
}

TEST_F(BinarySearchTest, FoundLast) {
    std::vector<int> data = {1, 2, 3, 5, 7, 8, 9};
    auto result = algo.search(std::span{data}, 9);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), 6);
}

TEST_F(BinarySearchTest, FoundDuplicates) {
    std::vector<int> data = {1, 2, 3, 3, 3, 8, 9};
    auto result = algo.search(std::span{data}, 3);
    ASSERT_TRUE(result.has_value());
    EXPECT_TRUE(result.value() >= 2 && result.value() <= 4);
}
