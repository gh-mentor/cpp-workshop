#include "robokit/control_loop.hpp"
#include "robokit/logging.hpp"
#include <chrono>

namespace robokit {

void ControlLoop::start() {
    if (running_) return;
    running_ = true;
    thread_ = std::thread([this]() {
        log::info("Control loop started");
        auto next = std::chrono::steady_clock::now();
        while (running_) {
            // busy wait for ~10ms period (inefficient)
            next += std::chrono::milliseconds(10);
            while (std::chrono::steady_clock::now() < next) { /* spin */ }
            // naive joint update
            for (auto& j : robot_.joints()) {
                j.position += 0.01; // arbitrary
            }
        }
        log::info("Control loop stopped");
    });
}

void ControlLoop::stop() {
    running_ = false;
    if (thread_.joinable()) thread_.join();
}

} // namespace robokit
