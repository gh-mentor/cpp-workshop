#include "robokit/robot.hpp"
#include "robokit/sensor.hpp"
#include "robokit/planner.hpp"
#include "robokit/control_loop.hpp"
#include "robokit/logging.hpp"
#include <iostream>

using namespace robokit;

int main() {
    Robot robot("demo_bot", 3);
    robot.add_sensor(new NoisySineSensor(1.0));
    robot.add_sensor(new RandomWalkSensor());
    Planner planner(10,10);
    ControlLoop loop(robot, planner);
    loop.start();
    for (int i=0;i<5;++i) {
        // naive sensor poll
        for (auto* s : robot.sensors()) {
            double v = s->read();
            std::cout << s->name() << ": " << v << '\n';
        }
    }
    loop.stop();
    return 0;
}
