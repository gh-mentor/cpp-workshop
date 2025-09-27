# Manufacturing Simulation Workshop (C++ / g++ / CMake)

(Primary specification: see `microchips.md`. This README provides structure, ordered prompts, and build/test guidance for a modern C++ implementation in VS Code.)

---

## 0. Project Structure

Target language: C++17 (or newer)
Build system: CMake
Compiler: g++ (GNU)
Testing: doctest

Suggested directory layout:
```
config/
domain/
engines/
interfaces/
logging/
metrics/
queue/
runtime/
util/
tests/
```

Key components:
- SimulationConfig
- SimpleRandom (single RNG wrapper)
- AssemblyEngine / QualityControlEngine
- InMemoryWidgetQueue
- InMemoryEventLog
- MetricsAggregator + DailySummary
- SimulationRunner (minute loop)
- main.cpp (CLI parsing: --days, --seed)

Design notes:
- Keep a single seeded RNG source (e.g. std::mt19937).
- All time uses minute indices (0..1439); no real-time clock calls.
- Prefer value types & RAII; avoid raw new/delete.
- Keep engines logic-focused; formatting only in main.

---

## 1. Scope Overview

Build a deterministic manufacturing + quality control simulation that emits daily metrics: production, damage, failures, downtime, inspection throughput, defects, accepted units, backlog, utilization, system efficiency.

---

## 2. Requirements Summary (Condensed)

Assembly (5 lines): 07:00–13:00 (360 mins). Base hourly throughput 80 (cap 100) with optional ±10 variance (apply variance only if variance > 0 OR a config flag enableVariance = true). Damage prob 0.005. Failure chance per line per day 0.10; at most one failure, downtime 60 mins. Hourly batch deliveries (end of each hour after first) plus final end-of-day.

Quality Control: 5 teams × 3 engineers. 08:00–16:00 (480 mins). Lunch 12:00–12:45 (no inspections). Per engineer capacity 8/hour → per-minute capacity floor((5*3*8)/60)=4. Defect probability 0.025.

Queue: FIFO. Only gets hourly (and final) batches of good (non-damaged) widgets.

Metrics: Produced/Damaged/Failures/Downtime per line, totals, inspected/defects/accepted, backlogEndOfDay, maxQueueLength, utilization per line ((360 - downtime)/360), systemEfficiency (accepted/goodProduced, guarded).

---

## 3. Acceptance Criteria

- Deterministic identical results for same seed/config.
- No inspection increments during lunch window.
- backlogEndOfDay > 0 with default config.
- Utilization < 1.0 if any failure; otherwise exactly 1.0.
- Bounds: damaged ≤ produced; goodProduced = produced - Σdamaged.
- defects ≤ inspected; accepted = inspected - defects.
- maxQueueLength ≥ backlogEndOfDay.
- Safe division (no crashes when zero production) → systemEfficiency = 0.0 when totalGoodProduced == 0.
- Core test run < 3s on typical dev machine.

---

## 4. Ordered Prompts (Use sequentially with Copilot)

1. "Create SimulationConfig with fields: days, seed, assemblyLineCount=5, qcTeamCount=5, engineersPerTeam=3, assemblyStart=7*60, assemblyMinutes=360, qcStart=8*60, qcMinutes=480, lunchStart=12*60, lunchMinutes=45, hourlyBaseThroughput=80, hourlyVariance=10, hourlyMax=100, damageProbability=0.005, failureChancePerLinePerDay=0.10, failureDowntimeMinutes=60, qcPerEngineerPerHour=8, defectProbability=0.025."
2. "Add TimeHelpers: bool isAssemblyMinute(int m), isQCMinute(int m), isLunch(int m)."
3. "Define structs: MicroWidget{id,lineId}; InspectionResult{widgetId,isDefective}; FailureEvent{lineId,startMinute,downtimeMinutes}."
4. "Create DailySummary with vectors for per-line counts and scalar totals; include utilization and systemEfficiency." 
5. "Add abstract interfaces: EventLog(append,snapshot), WidgetQueue(enqueueBatch,dequeueUpTo), AssemblyEngine(tick(minute)), QualityControlEngine(tick(minute)), MetricsAggregator(methods)."
6. "Implement InMemoryEventLog storing simple string messages." 
7. "Implement InMemoryWidgetQueue using std::queue<MicroWidget>." 
8. "Implement SimpleRandom wrapping std::mt19937 with nextInt(min,maxInclusive) and nextDouble()." 
9. "Implement AssemblyEngine: per-line state (producedThisHour, hourTarget, failed, downtimeLeft). Compute hourTarget at hour start with variance clamped to hourlyMax. Deliver batch on hour boundary or assembly end." 
10. "Add failure determination at day start; if failing set downtimeLeft. Produce zero while downtimeLeft > 0 (decrement each assembly minute)." 
11. "Implement QualityControlEngine: per-minute capacity, skip if lunch or outside QC window; dequeue up to capacity; classify defects by probability." 
12. "Implement MetricsAggregator updating all counters; upon each enqueue/dequeue, compare current queue size to maxQueueLength and update if larger." 
13. "Implement SimulationRunner: for each day loop minutes 0..1439, call engines, update metrics, finalize DailySummary for the day." 
14. "Implement main.cpp parsing --days and --seed (defaults: days=1, seed=123), run SimulationRunner, print summary in plain text." 
15. "Add doctest: deterministic same-seed run produces identical summaries (serialize & compare)." 
16. "Add doctest: inspection totals unchanged across lunch interval (no increments)." 
17. "Add doctest: backlogEndOfDay > 0 after one default day." 
18. "Add doctest: forcing failureChancePerLinePerDay=1 yields utilization < 1 for at least one line." 
19. "Add Doxygen comments to all public structs/classes/functions." 
20. (Optional) "Add defectRate = totalDefects / (double)totalInspected (guard zero) and multi-day aggregate." 

---

## 5. Suggested Timeline (≈2 Hours)

- 0–15: Config + models + RNG
- 15–35: Assembly engine + queue
- 35–55: QC engine + metrics aggregator
- 55–70: Runner + main + output formatting
- 70–90: doctest suites
- 90–105: Doxygen + polish
- Remaining: optional enhancements

---

## 6. Test Focus

- DeterminismTest
- LunchPauseTest
- BacklogPositiveTest
- UtilizationFailureTest
- (Optional) DamageDefectSanityTest (multi-day)

---

## 7. Quality Checklist

- Single seeded RNG instance
- No real-time system clock usage
- Engines isolated from formatting
- O(1) queue operations
- Doxygen comments added
- Warnings minimized (-Wall -Wextra -Wpedantic)
- Tests < 3s

---

## 8. Stretch Goals

- Per-minute wait / latency tracking
- Gaussian sampling option
- Scenario comparison runner
- CSV export
- Weekly summary aggregator

---

## 9. Quick Run

Build & run:
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

## 10. Future Extension

Add richer distributions, queue latency metrics, per-team metrics, multi-scenario analysis, data export formats.

---