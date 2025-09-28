#include "robokit/planner.hpp"
#include <queue>

namespace robokit {

Planner::Planner(int w, int h) : w_(w), h_(h), grid_(w*h, 0) {}

std::vector<std::pair<int,int>> Planner::plan(int sx, int sy, int gx, int gy) {
    // Basic BFS (no bounds checks robustness) intentionally naive.
    std::vector<int> visited(w_*h_, 0);
    std::queue<GridNode> q;
    q.push({sx, sy, 0});
    std::vector<std::pair<int,int>> path;
    while (!q.empty()) {
        auto n = q.front(); q.pop();
        if (n.x == gx && n.y == gy) {
            path.push_back({n.x,n.y});
            return path; // returns only goal (no reconstruction) intentionally incomplete
        }
        int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
        for (auto& d : dirs) {
            int nx = n.x + d[0];
            int ny = n.y + d[1];
            if (nx>=0 && nx<w_ && ny>=0 && ny<h_) {
                int idx = ny*w_ + nx;
                if (!visited[idx] && grid_[idx]==0) {
                    visited[idx]=1;
                    q.push({nx,ny,n.cost+1});
                }
            }
        }
    }
    return path; // empty if no path
}

} // namespace robokit
