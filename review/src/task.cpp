/*
The included header file "task.h" contains the definition of the function execute.
The function execute takes a function t and an integer load as arguments and executes the function t on a separate thread.
*/

#include "task.h"
#include <thread>
#include <future>
#include <iostream>

/*
This function executes a given task on a separate thread.
Arguments:
    t: a function that takes an integer as an argument and returns void.
    load: an integer that is passed to the function t which is used to simulate a workload.
Returns:
    void 
Exceptions:
    The function will throw an exception if the task t throws an exception.
*/
void execute(std::function<void(int)> t, int load) {
    std::packaged_task<void(int)> task(t);
    std::future<void> future = task.get_future();
    std::thread worker(std::move(task), load);
    worker.join();
    std::cout << "Task completed." << '\n';
    try {
        future.get();
    } catch (const std::exception& e) {
        std::cerr << "Task threw an exception: " << e.what() << '\n';
        throw;
    }
}
