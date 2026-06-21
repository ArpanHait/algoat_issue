add_library(algoat algoat.cpp core/traits.cpp core/config.cpp)

target_include_directories(algoat
    PUBLIC  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)
target_compile_features(algoat PUBLIC cxx_std_20)

include(FetchContent)
FetchContent_Declare(json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.12.0
)
FetchContent_MakeAvailable(json)
target_link_libraries(algoat PUBLIC nlohmann_json::nlohmann_json)
