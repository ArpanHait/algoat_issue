add_library(algoat "")

target_include_directories(algoat
    PUBLIC  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)
target_compile_features(algoat PUBLIC cxx_std_20)
