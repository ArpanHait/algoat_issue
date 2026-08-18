#include "algoat/core/config.hpp"

#include <gtest/gtest.h>
#include <stdexcept>
#include <string>

using namespace algoat::core;

// MACRO defined by CMake
#ifndef ALGOAT_TEST_FIXTURES_DIR
#error "ALGOAT_TEST_FIXTURES_DIR not defined"
#endif

std::string get_fixture_path(const std::string& filename) {
    return std::string(ALGOAT_TEST_FIXTURES_DIR) + "/" + filename;
}

TEST(ConfigTest, LoadsValidConfig) {
    auto config = load_config(get_fixture_path("valid.json"));

    ASSERT_TRUE(config.sorting.prefer.has_value());
    EXPECT_EQ(config.sorting.prefer.value(), "quicksort");

    ASSERT_TRUE(config.sorting.fallback.has_value());
    EXPECT_EQ(config.sorting.fallback.value(), "heapsort");

    ASSERT_TRUE(config.sorting.small_threshold.has_value());
    EXPECT_EQ(config.sorting.small_threshold.value(), 32);

    ASSERT_TRUE(config.searching.prefer.has_value());
    EXPECT_EQ(config.searching.prefer.value(), "binary_search");

    ASSERT_TRUE(config.searching.fallback.has_value());
    EXPECT_EQ(config.searching.fallback.value(), "linear_search");
}

TEST(ConfigTest, LoadsPartialConfig) {
    auto config = load_config(get_fixture_path("partial.json"));

    ASSERT_TRUE(config.sorting.prefer.has_value());
    EXPECT_EQ(config.sorting.prefer.value(), "mergesort");

    EXPECT_FALSE(config.sorting.fallback.has_value());
    EXPECT_FALSE(config.sorting.small_threshold.has_value());

    EXPECT_FALSE(config.searching.prefer.has_value());
    EXPECT_FALSE(config.searching.fallback.has_value());
}

TEST(ConfigTest, ThrowsOnNonexistentFile) {
    EXPECT_THROW(load_config(get_fixture_path("nonexistent.json")), std::runtime_error);
}

TEST(ConfigTest, ThrowsOnMalformedJson) {
    EXPECT_THROW(load_config(get_fixture_path("malformed.json")), std::runtime_error);
}
