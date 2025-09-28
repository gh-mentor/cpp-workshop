#pragma once
#include <vector>
#include <string>
#include <utility>
#include <cstdint>

namespace robokit {

struct GridNode { int x{}, y{}; int cost{}; };

class Planner {
public:
    Planner(int w, int h);
    // returns path as list of (x,y)
    std::vector<std::pair<int,int>> plan(int sx, int sy, int gx, int gy);

    // direct mutable access (unsafe) to occupancy grid
    std::vector<uint8_t>& grid() { return grid_; }
    const std::vector<uint8_t>& grid() const { return grid_; }
private:
    int w_, h_;
    std::vector<uint8_t> grid_; // 0 free, 1 obstacle
};

} // namespace robokit
