#pragma once
#include "robokit/robot.hpp"
#include "robokit/planner.hpp"
#include "robokit/kinematics.hpp"
#include <atomic>
#include <thread>
#include <functional>

namespace robokit {

class ControlLoop {
public:
    ControlLoop(Robot& robot, Planner& planner) : robot_(robot), planner_(planner) {}
    void start(); // busy wait loop (intentional inefficiency)
    void stop();
private:
    Robot& robot_;
    Planner& planner_;
    std::atomic<bool> running_{false};
    std::thread thread_;
};

} // namespace robokit
