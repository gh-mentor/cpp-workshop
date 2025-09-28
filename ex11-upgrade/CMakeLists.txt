cmake_minimum_required(VERSION 3.20)

project(RoboKit
    VERSION 0.1.0
    DESCRIPTION "Educational robotics baseline (C++20) for upgrade demonstrations"
    LANGUAGES CXX)

option(ROBOKIT_BUILD_TESTS "Build unit tests" ON)
option(ROBOKIT_WARNINGS_AS_ERRORS "Treat warnings as errors" OFF) # Intentionally off initially.

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Basic warnings (we will later tighten / add sanitizers in modernization phase)
if (MSVC)
    add_compile_options(/W3)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

if (ROBOKIT_WARNINGS_AS_ERRORS)
    if (MSVC)
        add_compile_options(/WX)
    else()
        add_compile_options(-Werror)
    endif()
endif()

# Sources (initially minimal; more will be added)
add_subdirectory(src)

if (ROBOKIT_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

message(STATUS "RoboKit configured. Tests: ${ROBOKIT_BUILD_TESTS}")
