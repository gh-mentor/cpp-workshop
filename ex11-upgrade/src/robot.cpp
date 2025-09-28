#include "robokit/robot.hpp"

namespace robokit {

Robot::Robot(std::string name, std::size_t dof) : name_(std::move(name)), joints_(dof) {}

Robot::~Robot() {
    // manual delete of owned sensors (ownership is unclear by design)
    for (auto* s : sensors_) {
        delete s; // potential polymorphic delete without virtual dtor? (SensorBase has virtual dtor)
    }
}

void Robot::add_sensor(SensorBase* s) {
    sensors_.push_back(s);
}

} // namespace robokit
