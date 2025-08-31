Use PowerShell for the proper execution of the commands.

## Testing

In tests/test_logger.cpp, implement the following test cases:

1) Test that the Logger is a singleton. 

2) Test the logging functionality. Use the following steps to verify the log messages:
-- Get the Logger instance
-- Log a test message
-- Verify that the log message was written to the file

3) Test the Logger's thread safety by logging from multiple threads simultaneously.
-- Create a number of threads that log messages
-- Verify that all messages are logged

4) Test logging multiple messages in sequence

## Requirements

- C++11 or later
- A C++ compiler (e.g., `g++`)
- POSIX threads library (`pthread`)

## Create a build directory

mkdir build
cd build

## Run CMake to configure the project with MinGW Makefiles

cmake -G "MinGW Makefiles" ..

## Build the project using mingw32-make

mingw32-make

## Run the test 

.\test_logger.exe --success

## Run the app

.\logger_app.exe 

## Return to the root directory

cd ..
