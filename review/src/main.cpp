/*
This app simulates a workload using a lambda function and a packaged task.
*/

/*
Include header for input/output stream, future, chrono, thread, functional, and random
*/
#include "task.h"
#include <iostream>
#include <future>
#include <chrono>
#include <thread>
#include <functional>
#include <random>
#include <stdexcept>

int main()
{

    /*
    Create a lambda function named 'job' that simulates a workload.
    Arguments:
    - 'workload': an integer representing the number of steps in the workload
    Returns: void
    Details:
    - Use a 'for loop' to to simulate a workload by iterating from the given workload value down to 1. 
    - For each iteration, it performs the following steps:
        1) Generates a random sleep time between 0.5 and 1.5 seconds.
        2) Pauses the execution for the generated sleep time.
        3) Prints a message indicating the completion of the current step.
    Errors:
    - If the workload is less than or equal to 0, the function should throw an invalid_argument exception with the message "Invalid workload value".
    Example:
    job(10);
    */
    auto job = [](int workload) -> void
    {
        for (int i = workload; i > 0; --i)
        {
            /*
            TODO: refactor the selected code into a new function 'uniform_distribution' that accepts 2 double args for the range of the distribution and returns a random double value within the range.
            */
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<double> dis(0.5, 1.5);
            double sleepTime = dis(gen);
            std::this_thread::sleep_for(std::chrono::duration<double>(sleepTime));
            // Log the completion message
            std::clog << "Completed step #" << i << '\n';
        }
    };

    const int steps = 10;
    execute(job, steps);

    return 0;
}
