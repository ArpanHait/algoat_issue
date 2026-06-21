include(FetchContent)
FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.16.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

function(algoat_add_test TEST_NAME TEST_SOURCE)
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    target_link_libraries(${TEST_NAME} PRIVATE algoat GTest::gtest_main)
    target_compile_definitions(${TEST_NAME} PRIVATE ALGOAT_TEST_FIXTURES_DIR="${PROJECT_SOURCE_DIR}/tests/core/fixtures")
    gtest_discover_tests(${TEST_NAME})
endfunction()

# Core tests
algoat_add_test(test_traits core/test_traits.cpp)
algoat_add_test(test_config core/test_config.cpp)
algoat_add_test(test_registry core/test_registry.cpp)
