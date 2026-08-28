#include "algoat/searching/binary_search.hpp"

#include <gtest/gtest.h>
#include <vector>

using namespace algoat::searching;

class BinarySearchTest : public ::testing::Test {
protected:
    BinarySearch algo;
};

TEST_F(BinarySearchTest, EmptySpan) {
    std::vector<int> data;
    auto result = algo.search(std::span{data}, 1);
    EXPECT_FALSE(result.has_value());

    std::span<const int> const_span{data.data(), data.size()};
    auto const_result = algo.search(const_span, 1);
    EXPECT_FALSE(const_result.has_value());
}

TEST_F(BinarySearchTest, SingleElement) {
    std::vector<int> data = {42};

    // Matching case
    auto result_match = algo.search(std::span{data}, 42);
    ASSERT_TRUE(result_match.has_value());
    EXPECT_EQ(result_match.value(), 0);

    // Non-matching cases (smaller and larger)
    auto result_smaller = algo.search(std::span{data}, 10);
    EXPECT_FALSE(result_smaller.has_value());

    auto result_larger = algo.search(std::span{data}, 100);
    EXPECT_FALSE(result_larger.has_value());
}

TEST_F(BinarySearchTest, OutOfBoundsTargets) {
    std::vector<int> data = {10, 20, 30, 40, 50};

    // Target smaller than data[0]
    auto result_smaller = algo.search(std::span{data}, 5);
    EXPECT_FALSE(result_smaller.has_value());

    // Target larger than data[N-1]
    auto result_larger = algo.search(std::span{data}, 60);
    EXPECT_FALSE(result_larger.has_value());
}

TEST_F(BinarySearchTest, DuplicateValues) {
    std::vector<int> data = {1, 3, 3, 3, 3, 3, 7};

    auto result = algo.search(std::span{data}, 3);
    ASSERT_TRUE(result.has_value());
    EXPECT_GE(result.value(), 1);
    EXPECT_LE(result.value(), 5);

    std::vector<int> all_dups = {5, 5, 5, 5};
    auto result_all = algo.search(std::span{all_dups}, 5);
    ASSERT_TRUE(result_all.has_value());
    EXPECT_GE(result_all.value(), 0);
    EXPECT_LE(result_all.value(), 3);
}

TEST_F(BinarySearchTest, EvenAndOddSizes) {
    // Two elements (even)
    std::vector<int> two_elems = {10, 20};
    EXPECT_EQ(algo.search(std::span{two_elems}, 10), 0);
    EXPECT_EQ(algo.search(std::span{two_elems}, 20), 1);
    EXPECT_FALSE(algo.search(std::span{two_elems}, 15).has_value());

    // Three elements (odd)
    std::vector<int> three_elems = {10, 20, 30};
    EXPECT_EQ(algo.search(std::span{three_elems}, 10), 0);
    EXPECT_EQ(algo.search(std::span{three_elems}, 20), 1);
    EXPECT_EQ(algo.search(std::span{three_elems}, 30), 2);
    EXPECT_FALSE(algo.search(std::span{three_elems}, 25).has_value());

    // Four elements (even)
    std::vector<int> four_elems = {10, 20, 30, 40};
    EXPECT_EQ(algo.search(std::span{four_elems}, 10), 0);
    EXPECT_EQ(algo.search(std::span{four_elems}, 20), 1);
    EXPECT_EQ(algo.search(std::span{four_elems}, 30), 2);
    EXPECT_EQ(algo.search(std::span{four_elems}, 40), 3);
    EXPECT_FALSE(algo.search(std::span{four_elems}, 5).has_value());
}

TEST_F(BinarySearchTest, ConstSpan) {
    const std::vector<double> data = {1.1, 2.2, 3.3, 4.4, 5.5};
    std::span<const double> const_span{data.data(), data.size()};

    auto res = algo.search(const_span, 3.3);
    ASSERT_TRUE(res.has_value());
    EXPECT_EQ(res.value(), 2);
}
