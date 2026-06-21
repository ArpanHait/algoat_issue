add_library(algoat algoat.cpp core/traits.cpp core/config.cpp core/registry.cpp core/dispatcher.cpp sorting/insertionsort.cpp sorting/quicksort.cpp sorting/mergesort.cpp sorting/heapsort.cpp searching/linear_search.cpp searching/binary_search.cpp searching/interpolation_search.cpp)

target_include_directories(algoat
    PUBLIC  
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)
target_compile_features(algoat PUBLIC cxx_std_20)

find_package(nlohmann_json QUIET)
if(NOT nlohmann_json_FOUND)
    include(FetchContent)
    FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG        v3.12.0
    )
    FetchContent_MakeAvailable(json)
endif()
target_link_libraries(algoat PUBLIC nlohmann_json::nlohmann_json)

include(GNUInstallDirs)

install(TARGETS algoat
    EXPORT AlgoatTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/algoat
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h"
)
