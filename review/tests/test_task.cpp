#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <functional>
#include <iostream>
#include <thread>
#include <future>

// Include the header where the execute function is declared
#include "../src/task.h"

// Mock function to be used with execute
void mock_function(int load) {
    std::cout << "Processing workload: " << load << '\n';
}

// Mock function that throws an exception
void mock_function_throw(int load) {
    throw std::runtime_error("Simulated exception");
}

// Test cases:
// - Test execute function
// - Test execute function with exception

TEST_CASE("Testing execute function") {
    CHECK_NOTHROW(execute(mock_function, 10));
    CHECK(true); // Add a simple assertion to ensure the test case runs
}

TEST_CASE("Testing execute function with exception") {
    CHECK_THROWS_AS(execute(mock_function_throw, 10), std::runtime_error);
}