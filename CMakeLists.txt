cmake_minimum_required(VERSION 3.20)
project(kiren VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories - src klasörünü de ekle
include_directories(include src)

# Find Google Test
find_package(GTest QUIET)

if(NOT GTest_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
    )
    FetchContent_MakeAvailable(googletest)
endif()

# Main Kiren library (without main.cpp)
add_library(kiren_lib
    src/core/runtime.cpp
    src/core/js_interpreter.cpp
    src/core/repl.cpp
)

target_include_directories(kiren_lib PUBLIC include src)

# Main executable
add_executable(kiren src/main.cpp)
target_link_libraries(kiren kiren_lib)

# Tests
enable_testing()

# Test files
add_executable(kiren_tests
    tests/test_main.cpp
    tests/test_runtime.cpp
    tests/test_js_interpreter.cpp
    tests/test_variables.cpp
)

target_link_libraries(kiren_tests 
    kiren_lib
    gtest
    gtest_main
)

# Tests'te de include path'leri ekle
target_include_directories(kiren_tests PRIVATE include src)

add_test(NAME KirenTests COMMAND kiren_tests)

add_custom_target(test_verbose 
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/kiren_tests --gtest_color=yes --gtest_output=verbose
    DEPENDS kiren_tests
)

# Debug settings
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall")

if(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()
