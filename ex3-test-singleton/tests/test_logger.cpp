#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "logger.h"
#include <thread>


// For all test cases, use the CHECK macro to verify conditions.


// Test the log file creation
TEST_CASE("Log File Creation") {
    std::remove("log.txt"); // Delete if exists
    Logger& logger = Logger::GetInstance();
    logger.Log("File creation test");
    std::ifstream logFile("log.txt");
    CHECK(logFile.good());
    logFile.close();
}
