#include "algoat/core/traits.hpp"

#include <gtest/gtest.h>
#include <vector>

using namespace algoat::core;

TEST(DataTraitsTest, EmptyData) {
    std::vector<int> data;
    auto traits = analyze(data);
    EXPECT_EQ(traits.size, 0);
    EXPECT_DOUBLE_EQ(traits.sortedness_ratio, 1.0);
    EXPECT_FALSE(traits.has_duplicates);
}

TEST(DataTraitsTest, SingleElement) {
    std::vector<int> data = {42};
    auto traits = analyze(data);
    EXPECT_EQ(traits.size, 1);
    EXPECT_DOUBLE_EQ(traits.sortedness_ratio, 1.0);
    EXPECT_FALSE(traits.has_duplicates);
}

TEST(DataTraitsTest, FullySorted) {
    std::vector<int> data = {1, 2, 3, 4, 5};
    auto traits = analyze(data);
    EXPECT_EQ(traits.size, 5);
    EXPECT_DOUBLE_EQ(traits.sortedness_ratio, 1.0);
    EXPECT_FALSE(traits.has_duplicates);
}

TEST(DataTraitsTest, ReverseSorted) {
    std::vector<int> data = {5, 4, 3, 2, 1};
    auto traits = analyze(data);
    EXPECT_EQ(traits.size, 5);
    EXPECT_DOUBLE_EQ(traits.sortedness_ratio, 0.0);
    EXPECT_FALSE(traits.has_duplicates);
}

TEST(DataTraitsTest, RandomData) {
    std::vector<int> data = {3, 1, 4, 2, 5};
    auto traits = analyze(data);
    EXPECT_EQ(traits.size, 5);
    // pairs: (3,1)=F, (1,4)=T, (4,2)=F, (2,5)=T. 2 sorted pairs out of 4.
    EXPECT_DOUBLE_EQ(traits.sortedness_ratio, 0.5);
    EXPECT_FALSE(traits.has_duplicates);
}

TEST(DataTraitsTest, AllDuplicates) {
    std::vector<int> data = {7, 7, 7, 7};
    auto traits = analyze(data);
    EXPECT_EQ(traits.size, 4);
    // pairs: (7,7)=T, (7,7)=T, (7,7)=T. 3 sorted pairs out of 3.
    EXPECT_DOUBLE_EQ(traits.sortedness_ratio, 1.0);
    EXPECT_TRUE(traits.has_duplicates);
}
