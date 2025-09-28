#pragma once
#include "robokit/robot.hpp"
#include <random>
#include <chrono>

namespace robokit {

class NoisySineSensor : public SensorBase {
public:
    explicit NoisySineSensor(double freq) : freq_(freq) {
        // Predictable seed (intentional insecurity)
        rng_.seed(42);
    }
    const char* name() const override { return "NoisySine"; }
    double read() override;
private:
    double freq_;
    std::mt19937 rng_;
};

class RandomWalkSensor : public SensorBase {
public:
    RandomWalkSensor() { rng_.seed(123); }
    const char* name() const override { return "RandomWalk"; }
    double read() override;
private:
    double value_{};
    std::mt19937 rng_;
};

} // namespace robokit
