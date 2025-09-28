# RoboKit (C++20 Baseline)

Educational robotics codebase intentionally written with shortcomings to showcase modernization:

1. Upgrade path from C++20 -> C++23.
2. Applying MISRA C++ / security hardening later.
3. Expanding minimal tests into a robust suite (property, fuzz, golden, coverage).

> DISCLAIMER: Not production ready. Unsafe patterns are present by design for teaching.

## Features (Current)
- Planar arm kinematics (very naive IK) – `robokit/kinematics.hpp`.
- Simple BFS grid planner (no path reconstruction / heuristics) – `robokit/planner.hpp`.
- Sensor simulation (sine + random walk) with predictable RNG seeds – `robokit/sensor.hpp`.
- Control loop using busy waiting, no deterministic timing – `robokit/control_loop.hpp`.
- Global logging macros with mutex – `robokit/logging.hpp`.
- Insecure config parsing – `robokit/config.hpp`.
- Manual memory management for sensors in `Robot` – `robokit/robot.hpp`.

## Intentional Issues / Smells
- Raw owning pointers (`Robot::add_sensor`).
- Lack of error handling (functions silently succeed/fail).
- Global logger state and side effects in headers.
- Naive BFS with no path reconstruction.
- Busy wait spin for timing.
- Non-deterministic time usage for sensor values (but deterministic seeds reduce entropy – security concern).
- Minimal test coverage (sanity only).

## C++23 Upgrade Opportunities
- `std::expected` for config + planner/kinematics error propagation.
- `std::mdspan` for matrix / Jacobian operations.
- `std::print` for logging & formatting (replacing iostream overhead and improving clarity).
- `std::ranges` algorithms to replace manual loops in planner and math utilities.
- `constexpr` evaluation for static grids / cost heuristics.
- `std::unreachable`, `[[assume]]` (where appropriate) after validation.
- `std::jthread` and `std::stop_token` for control loop management.


## Roadmap Snapshot
| Phase | Focus |
|-------|-------|
| 1 | Baseline (this) – insecure / naive C++20 |
| 2 | Incremental modernization (RAII, warnings, path fix) |
| 3 | Adopt C++23 features |
| 4 | MISRA + Security Hardening |
| 5 | Advanced Testing & Toolchain (coverage, fuzz, static analysis) |

## License
Educational example – choose a permissive license appropriate for your training context (not yet specified).
