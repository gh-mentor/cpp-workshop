#include "robokit/kinematics.hpp"
#include <cmath>

namespace robokit {

Pose2D Kinematics::forward(const std::vector<double>& joint_positions) {
    double x=0.0,y=0.0,theta=0.0;
    double acc_angle = 0.0;
    for (double a : joint_positions) {
        acc_angle += a;
        x += std::cos(acc_angle); // unit length links
        y += std::sin(acc_angle);
    }
    if (!joint_positions.empty()) theta = acc_angle;
    return {x,y,theta};
}

std::optional<std::vector<double>> Kinematics::inverse(const Pose2D& target, std::size_t dof) {
    // Extremely naive: evenly distribute angle, ignore position (not a real IK solution).
    if (dof == 0) return std::nullopt;
    std::vector<double> joints(dof, target.theta / static_cast<double>(dof));
    return joints;
}

} // namespace robokit
