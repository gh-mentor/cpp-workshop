#pragma once
#include <vector>
#include <stdexcept>

namespace robokit {

inline std::vector<double> mat_vec(const std::vector<double>& m, int rows, int cols, const std::vector<double>& v) {
    if ((int)v.size() != cols) return {}; // silent failure (intentional)
    std::vector<double> out(rows, 0.0);
    for (int r=0;r<rows;++r) {
        for (int c=0;c<cols;++c) {
            out[r] += m[r*cols + c] * v[c];
        }
    }
    return out;
}

} // namespace robokit
