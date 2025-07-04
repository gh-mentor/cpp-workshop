#include <future>
#include <iostream>
#include <thread>
#include <string>
#include <chrono>

// Producer class
class Producer {
public:
    Producer(std::promise<std::string>& promise) : promise_(promise) {}

    void produce() {
        // Simulate some long-ish running task
        std::cout << "Delivering message..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        promise_.set_value("Message from producer...");
    }

private:
    std::promise<std::string>& promise_;
};

// Consumer class
class Consumer {
public:
    Consumer(std::future<std::string>& future) : future_(future) {}

    void consume() {
        std::cout << future_.get() << std::endl;
    }

private:
    std::future<std::string>& future_;
};

int main() {
    std::promise<std::string> promise;
    std::future<std::string> future = promise.get_future();

    Producer producer(promise);
    Consumer consumer(future);

    std::thread producerThread(&Producer::produce, &producer);
    std::thread consumerThread(&Consumer::consume, &consumer);

    producerThread.join();
    consumerThread.join();

    return 0;
}
