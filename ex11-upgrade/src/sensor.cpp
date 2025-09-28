#include "robokit/sensor.hpp"
#include <cmath>
#include <random>

namespace robokit {

double NoisySineSensor::read() {
    std::uniform_real_distribution<double> noise(-0.01, 0.01);
    double t = static_cast<double>(std::chrono::steady_clock::now().time_since_epoch().count()) * 1e-9;
    return std::sin(freq_ * t) + noise(rng_);
}

double RandomWalkSensor::read() {
    std::uniform_real_distribution<double> step(-0.05, 0.05);
    value_ += step(rng_);
    return value_;
}

} // namespace robokit
