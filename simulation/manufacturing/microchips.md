## Manufacturing Simulation Specification (C++ Edition)

Authoritative specification for the manufacturing and quality control simulation. See `README-chips-scenario.md` for build order, ordered prompts, and implementation guidance targeted at modern C++ (g++/CMake/VS Code).

---

### 1. Objective

Simulate a manufacturing + quality control pipeline across 1..N days producing:
- Production, damaged units, failures and downtime
- Inspection throughput, defects, accepted units
- Backlog (end-of-day and maximum observed)
- Line utilization and system efficiency

Outputs:
- Per-day summaries
- Deterministic results when seed supplied
- Basic test suite validating core behaviors

---

### 2. Domain Constraints

Assembly:
- 5 lines
- Window: 07:00–13:00 (6 hours = 360 minutes)
- Base hourly throughput per line: 80 (cap 100)
- Optional uniform variance: ±10 (if enabled)
- Damage probability: 0.005 per produced unit (damaged not added to queue)
- Failure probability per line per day: 0.10 (≤1 failure; fixed 60-minute downtime)
- Hourly batch delivery at each hour boundary (after first hour) plus final end-of-day delivery

Quality Control:
- 5 teams × 3 engineers
- Window: 08:00–16:00 (8 hours)
- Lunch: 12:00–12:45 inclusive (no inspections)
- Per engineer hourly inspection capacity: 8
  - Total per-minute capacity = floor((5 * 3 * 8)/60) = 4
- Defect probability: 0.025 (defective counted; accepted = inspected - defects)

Queue:
- FIFO, unbounded
- Only populated by assembly batch deliveries
- QC pulls up to computed capacity per active minute

Time Representation:
- Day simulated as integer minute index 0..1439
- Multi-day simulation loops per-day; metrics per day isolated then aggregated externally if needed

---

### 3. Models

Recommended C++ data shapes (structs / POD style):
- MicroWidget { std::uint64_t id; int lineId; }
- FailureEvent { int lineId; int startMinute; int downtimeMinutes; }
- InspectionResult { std::uint64_t widgetId; bool isDefective; }
- DailySummary
   - std::vector<int> producedPerLine
   - std::vector<int> damagedPerLine
   - std::vector<int> failuresPerLine
   - std::vector<int> downtimeMinutesPerLine
   - int totalProduced
   - int totalGoodProduced
   - int totalInspected
   - int totalDefects
   - int totalAccepted
   - int backlogEndOfDay
   - int maxQueueLength
   - std::vector<double> lineUtilizationPerLine
   - double systemEfficiency

---

### 4. Functional Requirements

1. Minute-based simulation loop.
2. Assembly minute:
   - If line not failed and inside assembly window: accumulate production toward current hour target.
   - On hour boundary or assembly end: deliver produced widgets (good only), reset hour counters.
3. Failure:
   - Determine at start of day (or earliest assembly minute) if line will fail (probability check).
   - If failing: apply fixed 60-minute downtime where line produces zero.
4. Damage classification per produced widget; damaged excluded from queue and counted.
5. QC minute (within QC window and not lunch):
   - Dequeue up to capacity; classify each for defect probability.
6. Track queue length changes; update MaxQueueLength.
7. End-of-day calculations:
   - Utilization = (ScheduledMinutes - DowntimeMinutes)/ScheduledMinutes (ScheduledMinutes=360)
   - SystemEfficiency = TotalAccepted / TotalGoodProduced (0 if TotalGoodProduced = 0)

---

### 5. Non-Functional Requirements

- Deterministic output with fixed seed (single RNG instance, e.g. std::mt19937 seeded once)
- Single-threaded; no forced parallelism
- Console reporting (plain text) acceptable
- Doxygen documentation on public types / functions
- Test suite deterministic (avoid flaky statistical assertions)
- Clean build (no unused headers, -Wall -Wextra warnings addressed)

---

### 6. Acceptance Criteria

- Same seed + config → identical DailySummary data
- No inspections during lunch (inspection totals unchanged across lunch interval)
- backlogEndOfDay > 0 under default configuration
- Utilization < 1.0 if any line failed; otherwise exactly 1.0
- damaged ≤ totalProduced and totalGoodProduced = totalProduced - Σdamaged
- defects ≤ totalInspected and totalAccepted = totalInspected - totalDefects
- maxQueueLength ≥ backlogEndOfDay
- systemEfficiency computed safely (guard divide-by-zero)

---

### 7. Out of Scope

- Gaussian/normal distributions
- Variable failure downtime
- Queue wait time / latency statistics
- Per-team or per-engineer breakdown metrics
- Scenario comparison tooling
- Export formats (CSV/JSON)
- Event-driven time skipping
- Advanced probability tolerance validation

---

### 8. Stretch Enhancements (Optional)

- Introduce variance & Gaussian sampling
- Weekly summary aggregation object
- Queue latency tracking (enqueue vs inspection minute)
- Per-team metrics and utilization
- Multi-scenario runner and comparison report
- Data export (CSV/JSON)

---

### 9. Testing Outline (doctest)

- DeterminismTests: duplicate runs comparison
- LunchBreakTests: inspection count invariant across lunch window
- BacklogTests: default config yields positive backlog
- FailureUtilizationTests: forced failure probability → utilization reduction
- DamageDefectSanityTests: multi-day run produces non-zero damage & defects when probabilities > 0

---

### 10. Execution

Build (example):
```
cmake -S . -B build
cmake --build build --config Release
./build/simulation --days 1 --seed 123
```

Run tests:
```
./build/tests
```

---

### 11. Design Note

Structure (engines + queue + metrics) enables incremental enhancement without reworking the control loop. Favor value types, RAII, and standard containers (std::queue, std::vector). Keep RNG centralized to guarantee determinism.

---
