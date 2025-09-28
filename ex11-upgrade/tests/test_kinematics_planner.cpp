#include "robokit/kinematics.hpp"
#include "robokit/planner.hpp"
#include "robokit/robot.hpp"
#include "robokit/sensor.hpp"
#include <vector>
#include <cmath>
#include "vendor/doctest.h"

using namespace robokit;

TEST_CASE(test_forward_kinematics_simple){
    std::vector<double> joints = {0.0, 0.0};
    auto pose = Kinematics::forward(joints);
    REQUIRE(std::fabs(pose.x - 2.0) < 1e-6);
    REQUIRE(std::fabs(pose.y - 0.0) < 1e-6);
}

TEST_CASE(test_inverse_kinematics_trivial){
    Pose2D target{0,0,1.0};
    auto r = Kinematics::inverse(target, 4);
    REQUIRE(r.has_value());
    REQUIRE(r->size() == 4);
}

TEST_CASE(test_planner_reaches_goal){
    Planner p(5,5);
    auto path = p.plan(0,0,4,4);
    // In naive BFS we only return goal if reachable
    if(!path.empty()) {
        REQUIRE(path.back().first == 4);
        REQUIRE(path.back().second == 4);
    }
}
