#pragma once
#include <vector>
#include <array>
#include <optional>

namespace robokit {

// Simple planar arm forward kinematics (assumes unit length links for now)
// TODO(CPP23): Replace with std::mdspan for matrix operations.
struct Pose2D { double x{}, y{}, theta{}; };

class Kinematics {
public:
    static Pose2D forward(const std::vector<double>& joint_positions);
    static std::optional<std::vector<double>> inverse(const Pose2D& target, std::size_t dof);
};

} // namespace robokit
