## Pipeline with Concurrency Patterns in Modern C++

This exercise involves designing and implementing a C++ program using concurrency patterns with threads, tasks, and queues. The pipeline processes data through three stages: generator, processor, and aggregator, demonstrating how data flows between stages using thread-safe queues and concurrency mechanisms.

### Overview
The application consists of:
1. **Pipeline**: Orchestrates the execution of the three-stage pipeline.
2. **Generator**: Produces random integers within a configurable range and sends them to the processor.
3. **Processor**: Applies a computational transformation (e.g., factorial) to the integers and sends results to the aggregator.
4. **Aggregator**: Consolidates results (e.g., sum or average) and outputs a summary.
5. **Main function**: Initializes and starts the pipeline, managing threads and handling errors.
6. **Tests**: Validates the functionality of each stage and the overall pipeline.

### Project Setup Instructions

1. **Create the Project Structure**:
   - `CMakeLists.txt`: Defines the build system and dependencies. Place this file in the root directory of the project.
   - `src/main.cpp`: Initializes the pipeline and manages threads.
   - `src/pipeline.hpp` and `src/pipeline.cpp`: Implements the overall pipeline structure and flow.
   - `src/generator.hpp` and `src/generator.cpp`: Implements the generator stage.
   - `src/processor.hpp` and `src/processor.cpp`: Implements the processor stage.
   - `src/aggregator.hpp` and `src/aggregator.cpp`: Implements the aggregator stage.
   - `tests/`: Contains unit tests for each component using the `doctest` testing framework.

2. **Add a `.gitignore` File**:
   - Exclude unnecessary files such as build artifacts, temporary files, and IDE-specific files.

3. **Configure `doctest`**:
   - The `doctest.h` header is already included in the `./tests/` folder. You can directly include it in your test files.
   - Ensure your `CMakeLists.txt` file is configured to include the `tests/` directory in the include paths:
     ```cmake
     include_directories(tests)
     ```
   - Do not link `doctest` as a library since it is header-only. Simply include the header in your test files.
   - To ensure tests are discovered and the build works, add the following as the first line of your main test file (e.g., `pipeline_test.cpp`):
     ```cpp
     #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
     ```
   - Only one test file should contain this line; all other test files should simply include `doctest.h`.
   - This provides the test runner entry point and avoids linker errors or missing tests.

4. **Build and Test**:
   - Use the following commands to build and test the project on Windows with GNU C++ (g++):
     ```bash
     mkdir build && cd build
     cmake -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=g++ ..
     mingw32-make
     ctest
     ```
   - Ensure that the `PipelineLib` shared library is properly set up in `CMakeLists.txt` and linked to the test targets.
   - If you see an error about `undefined reference to WinMain`, ensure your CMakeLists.txt contains:
     ```cmake
     set_target_properties(tests PROPERTIES WIN32_EXECUTABLE OFF)
     ```
     - This ensures the test executable is built as a console application, not a Windows GUI application.

5. **Common Issues and Fixes**:
   - **Duplicate Definitions**: Ensure that `thread_safe_queue.hpp` is included only once in each translation unit to avoid duplicate definitions.
   - **Unresolved References**: Verify that all source files are added to the `PipelineLib` target in `CMakeLists.txt`.
   - **Header-Only Libraries**: Remember that `doctest` is header-only and does not require linking.


### Specifications

#### Main Function (`src/main.cpp`)
- Initializes and starts the pipeline, which consists of three stages: generator, processor, and aggregator.
- Configures command-line arguments:
  - `--min` and `--max`: Define the range of integers to generate.
  - `--count`: Specifies the number of integers to generate.
- Validates input values:
  - Ensures `min < max`.
  - Ensures `count > 0`.
- Creates thread-safe queues for communication between stages:
  - `generator -> processor`: A queue to send generated integers.
  - `processor -> aggregator`: A queue to send processed results.
- Uses `std::thread` and `std::future` to manage concurrency.
- Handles errors gracefully:
  - Logs errors to the console.
  - Ensures all threads are joined properly.
- Implements a signal handler to gracefully terminate the pipeline on receiving `SIGINT` or `SIGTERM`.

#### Pipeline (`src/pipeline.hpp` and `src/pipeline.cpp`)
- Orchestrates the execution of the three-stage pipeline.
- Manages the flow of data between the generator, processor, and aggregator stages using thread-safe queues.
- Starts the generator, processor, and aggregator as separate threads.
- Ensures proper cleanup:
  - Closes queues when a stage completes.
  - Handles errors and propagates them to the main function if necessary.
- Provides a function `void StartPipeline(int min, int max, int count)` to initialize and run the pipeline.

#### Generator (`src/generator.hpp` and `src/generator.cpp`)
- Produces random integers within a configurable range (`min` to `max`) and sends them to the processor stage.
- Accepts the following parameters:
  - `min`: Minimum value of the range.
  - `max`: Maximum value of the range.
  - `count`: Number of integers to generate.
  - `outQueue`: A thread-safe queue to send the generated integers.
- Introduces random delays (e.g., `std::this_thread::sleep_for`) to simulate asynchronous behavior.
- Uses multiple threads to generate integers concurrently, with all threads writing to the same output queue.
- Closes the output queue when all integers are generated.

#### Processor (`src/processor.hpp` and `src/processor.cpp`)
- Applies a computational transformation (e.g., factorial) to each integer received from the generator and sends the results to the aggregator.
- Accepts the following parameters:
  - `inQueue`: A thread-safe queue to receive integers from the generator.
  - `outQueue`: A thread-safe queue to send processed results to the aggregator.
- Uses multiple threads to process integers concurrently, with all threads writing to the same output queue.
- Handles edge cases:
  - Ensures the transformation function (e.g., factorial) handles large numbers without causing overflow.
- Closes the output queue when all integers are processed.

#### Aggregator (`src/aggregator.hpp` and `src/aggregator.cpp`)
- Consolidates results received from the processor and outputs a summary (e.g., sum or average).
- Accepts the following parameters:
  - `inQueue`: A thread-safe queue to receive processed results from the processor.
- Processes all results from the input queue and produces a single consolidated output (e.g., a sum or average).
- Outputs the final result to the console or a log file.
- Handles edge cases:
  - Ensures the summary calculation is accurate even if no data is received (e.g., `count = 0`).

### Testing

#### Generator (`tests/generator_test.cpp`)
- Validates that the generator produces the correct number of integers (`count`) within the specified range (`min` to `max`).
- Handles edge cases:
  - Ensures no integers are generated when `min == max`.
  - Ensures no integers are generated and the queue is closed properly when `count = 0`.
  - Handles large ranges to ensure performance and correctness.
- Uses multiple threads to validate concurrency:
  - Ensures integers are generated without race conditions or deadlocks.
- Handles invalid input values (e.g., `min > max`) gracefully.

#### Processor (`tests/processor_test.cpp`)
- Validates that the processor applies the transformation function (e.g., factorial) correctly to all integers received.
- Handles edge cases:
  - Ensures the transformation function handles small and large integers (e.g., factorial of 0 or large numbers).
  - Handles invalid inputs (if applicable) gracefully.
- Uses multiple threads to validate concurrency:
  - Ensures integers are processed without race conditions or deadlocks.
- Handles queue closures and unexpected input gracefully.

#### Aggregator (`tests/aggregator_test.cpp`)
- Validates that the aggregator consolidates results (e.g., sum or average) correctly.
- Handles edge cases:
  - Ensures the aggregator handles empty data gracefully when no input is received.
  - Ensures correctness with a single input.
  - Handles large datasets to ensure performance and correctness.
- Uses multiple threads to validate concurrency:
  - Ensures results are consolidated without race conditions or deadlocks.
- Handles queue closures and unexpected input gracefully.

#### Pipeline (`tests/pipeline_test.cpp`)
- Validates that the pipeline stages (generator, processor, aggregator) work together correctly and in order.
- Handles edge cases:
  - Ensures the pipeline works correctly with `count = 0`, `min == max`, and large ranges.
- Uses multiple threads to validate concurrency:
  - Ensures the pipeline handles concurrent operations across all stages without race conditions or deadlocks.
- Validates error propagation:
  - Ensures errors in any stage are propagated correctly to the main function.
- Validates signal handling:
  - Ensures the pipeline terminates gracefully on receiving `SIGINT` or `SIGTERM`.







