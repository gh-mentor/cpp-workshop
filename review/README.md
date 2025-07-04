# Packaged Task App

This app simulates a workload using a lambda function and a packaged task.

## Description

The application defines a function named `execute` that executes a given packaged task in a separate thread. It also defines a lambda function named `job` that simulates a workload by generating random sleep times and printing completion messages for each step.

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

## Run the test (PowerShell)

.\test_task.exe --success

## Return to the root directory

cd ..
