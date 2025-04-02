cmake_minimum_required(VERSION 3.10)

# Project name
project(FactoryAssemblyLineProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the source files for the FactoryAssemblyLine library
add_library(FactoryAssemblyLine
    src/FactoryAssemblyLine.cpp
    src/FactoryAssemblyLine.h
)

# Add the GoogleTest submodule (if you cloned it into your project)
# Alternatively, you can use the system-installed GoogleTest
# Uncomment the following lines if you have GoogleTest as a submodule:
# add_subdirectory(googletest)
# include_directories(googletest/include)

# Find GoogleTest (if installed on your system)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add the test executable
add_executable(FactoryAssemblyLineTest
    tests/FactoryAssemblyLineTest.cpp
)

# Link the test executable with the FactoryAssemblyLine library and GoogleTest
target_link_libraries(FactoryAssemblyLineTest
    FactoryAssemblyLine
    ${GTEST_LIBRARIES}
    pthread # Required for GoogleTest on some systems
)

# Enable testing
enable_testing()

# Add a test target
add_test(NAME FactoryAssemblyLineTest COMMAND FactoryAssemblyLineTest)