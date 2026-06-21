#include <gtest/gtest.h>
#include "algoat/searching/linear_search.hpp"
#include <vector>

using namespace algoat::searching;

class LinearSearchTest : public ::testing::Test {
protected:
    LinearSearch algo;
};

TEST_F(LinearSearchTest, FoundMiddle) {
    std::vector<int> data = {5, 3, 8, 1, 9, 2, 7};
    auto result = algo.search(std::span{data}, 1);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), 3);
}

TEST_F(LinearSearchTest, NotFound) {
    std::vector<int> data = {5, 3, 8, 1, 9, 2, 7};
    auto result = algo.search(std::span{data}, 42);
    EXPECT_FALSE(result.has_value());
}

TEST_F(LinearSearchTest, EmptyInput) {
    std::vector<int> data;
    auto result = algo.search(std::span{data}, 1);
    EXPECT_FALSE(result.has_value());
}

TEST_F(LinearSearchTest, FoundFirst) {
    std::vector<int> data = {5, 3, 8, 1, 9, 2, 7};
    auto result = algo.search(std::span{data}, 5);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), 0);
}

TEST_F(LinearSearchTest, FoundLast) {
    std::vector<int> data = {5, 3, 8, 1, 9, 2, 7};
    auto result = algo.search(std::span{data}, 7);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), 6);
}

TEST_F(LinearSearchTest, DuplicatesReturnsFirst) {
    std::vector<int> data = {5, 3, 8, 3, 9, 3, 7};
    auto result = algo.search(std::span{data}, 3);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), 1);
}
