# RoboKit Architecture (C++20 Baseline)

This project is a deliberately simplified, educational robotics codebase meant to:

1. Provide realistic modular structure (robot model, kinematics, sensors, planning, control, config, logging).
2. Contain intentional shortcomings (performance, safety, security, style) for later refactoring.
3. Offer many clear upgrade targets when moving from C++20 to C++23 and applying guidelines (MISRA C++, security hardening, testing rigor).

> WARNING: This code is intentionally NOT production‑grade. It uses unsafe patterns (raw pointers, unchecked parsing, poor error handling) for instructional contrast.

---

## Module Overview

| Module | Responsibility | Notes / Intentional Issues | C++23 / Hardening Opportunities |
|--------|----------------|----------------------------|---------------------------------|
| `Robot` | Aggregates joints, sensors, state. | Uses raw pointer ownership for a sensor list. | Replace with smart pointers + `std::pmr` or `std::vector` reserve strategies. |
| `Kinematics` | Forward / inverse kinematics for a planar arm (2–6 DOF extensible). | Naive Jacobian inversion (no damping / singularity handling). | Use `std::mdspan` (C++23) for matrix views; structured error via `std::expected`. |
| `Sensor` | Simulated Lidar & IMU noise models. | Random seeding ad-hoc; returns raw pointers. | Use strong types, `std::chrono` time stamps, `std::ranges` pipelines. |
| `Planner` | Grid + simple BFS/A* hybrid. | Manual queue + raw loops; no heuristics tuning. | Refactor with `std::ranges`, views, `constexpr` cost tables, `std::expected` for failures. |
| `ControlLoop` | Periodic update integrating sensor + planner + kinematics. | Busy wait timing, magic numbers, weak error propagation. | Introduce scheduler abstraction, `std::jthread`, `std::stop_token`, `std::chrono::utc_clock` (C++20/23). |
| `Logging` | Minimal macro-based logging to stdout. | Uses global mutable state; no severity filtering. | Replace with RAII logger, `std::print` (C++23), sinks, compile-time format strings. |
| `Config` | Reads naive key=value & pseudo‑JSON blend. | Unchecked buffer use, no validation, no escaping. | Harden parsing, use `std::string_view`, span, `std::expected`. |
| `Math` | Small linear algebra helpers. | Manual loops; no SIMD; potential UB on size mismatch. | Introduce `std::mdspan`, ranges algorithms, constexpr evaluation. |

---

## Error Handling Strategy (Current vs Desired)

Current: mixture of bool/int return codes, silent ignores.

Planned: layered approach
- Use `std::expected<T, Error>` (C++23 target) or a backported equivalent.
- Central error category enum.
- Propagate context with lightweight wrapper.

---

## Memory & Ownership (Current Issues)
- Raw `new/delete` for sensors.
- Borrowed views are raw pointers without lifetime guarantees.
- No custom allocators; reallocation churn in planner grid.

Upgrade Path
- Introduce smart pointers (`std::unique_ptr` / `std::shared_ptr` where justified).
- Use `std::span` for non-owning views (C++20 already; highlight upgrade by contrasting existing raw pointer code first).
- Potential polymorphic allocators for path planning experiments.

---

## Concurrency (Future Scope)
Current loop is single-threaded & uses busy wait.

Refactor Steps Later
1. Replace busy wait sleep with `std::this_thread::sleep_for` (baseline) then `std::jthread` w/ cooperative stop.
2. Partition sensor simulation vs planning in separate threads guarded by message queues.
3. Explore hazards for MISRA compliance: data races, non-determinism.

---

## Security / Safety Gaps (Intentional)
- Unbounded file reads into fixed buffers (`Config`).
- Lack of input sanitization (planner map data, config numeric ranges).
- Global mutable logger state.
- Predictable RNG seeding.

These become concrete before/after examples in later hardening phases.

---

## Testing Baseline
Minimal doctest suite (sanity tests only) to show contrast with later:
- Property-based tests
- Deterministic seeding harness
- Golden master path regression

---

## C++23 Opportunity Tags
Code will include comments in the form:
```
// TODO(CPP23): Replace manual variant visitation with std::visit + new features.
// TODO(CPP23): Use std::expected for error propagation.
```
These serve as anchors for upgrade walkthroughs.

---

## Roadmap Snapshot
Phase 1 (now): Insecure / naive baseline (C++20) with educational smells.

Phase 2: Incremental modernization (still C++20) – add warnings, RAII, partial tests.

Phase 3: C++23 upgrade + feature adoption.

Phase 4: MISRA & Security Hardening (reduce undefined behavior, sanitize inputs, formalize error handling).

Phase 5: Advanced Testing & Tooling (coverage, fuzzing, static analysis integration).

---

## Disclaimer
Not for production or safety-critical robot control. Real robotic software requires rigorous validation, deterministic real-time scheduling, and strict safety interlocks—omitted here intentionally.
