#include "algoat/core/registry.hpp"

#include <algorithm>
#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace algoat::core;

struct MockAlgo {
    std::string name;
};

using MockRegistry = Registry<MockAlgo>;

TEST(RegistryTest, RegisterAndCreate) {
    MockRegistry registry;
    registry.register_algo("algo1", []() { return MockAlgo{"algo1_instance"}; });

    ASSERT_TRUE(registry.has("algo1"));
    auto instance = registry.create("algo1");
    EXPECT_EQ(instance.name, "algo1_instance");
}

TEST(RegistryTest, DuplicateRegistrationThrows) {
    MockRegistry registry;
    registry.register_algo("algo1", []() { return MockAlgo{"first"}; });

    EXPECT_THROW(registry.register_algo("algo1", []() { return MockAlgo{"second"}; }),
                 std::runtime_error);
}

TEST(RegistryTest, UnknownNameThrows) {
    MockRegistry registry;
    EXPECT_THROW(registry.create("unknown"), std::runtime_error);
}

TEST(RegistryTest, ListRegistered) {
    MockRegistry registry;
    registry.register_algo("algo2", []() { return MockAlgo{"a2"}; });
    registry.register_algo("algo1", []() { return MockAlgo{"a1"}; });

    auto registered = registry.list_registered();
    EXPECT_EQ(registered.size(), 2);

    // std::unordered_map order is not guaranteed, so sort before checking
    std::sort(registered.begin(), registered.end());
    EXPECT_EQ(registered[0], "algo1");
    EXPECT_EQ(registered[1], "algo2");
}
