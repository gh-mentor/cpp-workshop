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

// Test that the Logger is a singleton. 
TEST_CASE("Testing Logger") {
    Logger& logger1 = Logger::GetInstance();
    Logger& logger2 = Logger::GetInstance();

    CHECK(&logger1 == &logger2);
}

// Test the logging functionality. Use the following steps to verify the log messages:
// 1. Get the Logger instance
// 2. Log a test message
// 3. Verify that the log message was written to the file
TEST_CASE("Logging Messages") {
    Logger& logger = Logger::GetInstance();

    logger.Log("Test log message");

    // Verify that the log message was written to the file
    std::ifstream logFile("log.txt");
    std::string line;
    bool messageFound = false;
    while (std::getline(logFile, line)) {
        if (line == "Test log message") {
            messageFound = true;
            break;
        }
    }
    logFile.close();

    CHECK(messageFound);
}



// Test the Logger's thread safety by logging from multiple threads simultaneously.
// - Create a number of threads that log messages
// - Verify that all messages are logged
TEST_CASE("Thread Safety") {
    Logger& logger = Logger::GetInstance();
    const int numThreads = 10;
    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back([i, &logger]() {
            logger.Log("Thread message " + std::to_string(i));
        });
    }
    for (auto& t : threads) t.join();

    std::ifstream logFile("log.txt");
    std::string line;
    int found = 0;
    while (std::getline(logFile, line)) {
        if (line.find("Thread message") != std::string::npos) {
            ++found;
        }
    }
    logFile.close();
    CHECK(found >= numThreads);
}

// Test logging multiple messages in sequence
TEST_CASE("Multiple Log Messages") {
    Logger& logger = Logger::GetInstance();
    logger.Log("First message");
    logger.Log("Second message");

    std::ifstream logFile("log.txt");
    std::vector<std::string> messages;
    std::string line;
    while (std::getline(logFile, line)) {
        messages.push_back(line);
    }
    logFile.close();

    CHECK(std::find(messages.begin(), messages.end(), "First message") != messages.end());
    CHECK(std::find(messages.begin(), messages.end(), "Second message") != messages.end());
}



