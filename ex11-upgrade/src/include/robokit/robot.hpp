#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include <memory>

namespace robokit {

struct JointState {
    double position{}; // radians
    double velocity{}; // radians/sec
};

class SensorBase {
public:
    virtual ~SensorBase() = default;
    virtual const char* name() const = 0;
    virtual double read() = 0; // simplistic single value
};

class Robot {
public:
    explicit Robot(std::string name, std::size_t dof);
    ~Robot(); // manual cleanup (intentional raw new usage)

    Robot(const Robot&) = delete;
    Robot& operator=(const Robot&) = delete;

    const std::string& name() const { return name_; }
    std::vector<JointState>& joints() { return joints_; }
    const std::vector<JointState>& joints() const { return joints_; }

    void add_sensor(SensorBase* s); // raw pointer ownership (intentional)
    std::vector<SensorBase*> sensors() const { return sensors_; } // returns copy of raw pointers

private:
    std::string name_;
    std::vector<JointState> joints_;
    std::vector<SensorBase*> sensors_;
};

} // namespace robokit
