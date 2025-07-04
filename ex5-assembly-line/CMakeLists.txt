cmake_minimum_required(VERSION 3.10)

# Project name
project(FactoryAssemblyLine)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
add_library(FactoryAssemblyLine src/FactoryAssemblyLine.cpp)

# Add executable for tests
add_executable(FactoryAssemblyLineTest tests/FactoryAssemblyLineTest.cpp tests/main.cpp) # Include main.cpp here

# Include directories
target_include_directories(FactoryAssemblyLine PUBLIC src)
target_include_directories(FactoryAssemblyLineTest PUBLIC src tests)

# Link the library to the test executable
target_link_libraries(FactoryAssemblyLineTest FactoryAssemblyLine)

# Enable testing
enable_testing()

# Add test using CTest
add_test(NAME FactoryAssemblyLineTest COMMAND FactoryAssemblyLineTest)