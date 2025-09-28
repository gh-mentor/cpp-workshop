# RoboKit Upgrade Script (Ordered Copilot / Assistant Prompts)

Usage:
- Feed one prompt at a time to the assistant.
- Commit after each prompt (message: `Prompt <n>: <short title>`).
- Do not batch multiple structural changes together.
- Maintain green tests after every step.

Legend:
- Tags to add in code: TODO(CPP23), TODO(SEC), TODO(MISRA), TODO(TEST), TODO(PERF)
- Coverage Target: 100% line + branch (justify any exclusions explicitly).

---

## Phase 1 – Baseline Audit & Foundation (C++20)

Prompt 1:
Audit the repository. Produce a table with columns: Area | Issue | Risk | Quick Win. Cover: memory ownership, error handling, concurrency, security (config + planner inputs), logging/global state, test gaps. Conclude with a prioritized Top 10 remediation list (short rationale each). No code yet.

Prompt 2:
Patch CMake to: enforce C++20, add maximum warnings for GCC/Clang/MSVC, add option BUILD_STRICT (ON by default) that turns warnings into errors, and optional SANITIZERS (address+undefined on supported compilers). Return only patch.

Prompt 3:
Insert standardized comment anchors (no logic changes) where modernization or hardening will occur. Add TODO(CPP23), TODO(SEC), TODO(MISRA), TODO(TEST) tags in relevant headers/source. Return diff snippets only (avoid duplicating existing tags).

Prompt 4:
Append to ARCHITECTURE.md a “Planner Invariants” section (grid bounds, coordinate system, blocked cell semantics). Return patch only.

Prompt 5:
Create CONTRIBUTING.md containing: commit message convention, tag taxonomy, branching model (main + feature/*), test expectation (must add or update tests per change), coding style pre-MISRA (brace style, naming, includes order). Return file only.

Prompt 6:
Generate INITIAL_RISK_BASELINE.md summarizing audit metrics: raw pointer sites count, functions without error handling count, global mutable singletons count. Include a table; no code modifications.

---

## Phase 2 – Incremental Modernization (Still C++20)

Prompt 7:
Design RAII migration plan for sensors. Provide phased steps:
1. Introduce unique_ptr in Robot internal container.
2. Provide non-owning accessors (span or const references).
3. Remove manual delete.
Return plan + first patch (data member + ctor adjustments only).

Prompt 8:
Complete RAII migration (apply steps 2–3). Ensure tests build. Return patch.

Prompt 9:
Implement path reconstruction in planner (BFS) returning std::vector<std::pair<int,int>>. Add tests: straight path, blocked goal, detour. Return changed files + new tests only.

Prompt 10:
Introduce a lightweight Result<T,E> (no dynamic alloc) in result.hpp. Refactor planner plan() to return Result<Path, PlannerError>. Update affected tests. Return patch.

Prompt 11:
Externalize logging implementation to logging.cpp with macro guard ROBOKIT_ENABLE_LOGGING (default ON). Preserve API. Return patch.

Prompt 12:
Add test_support.hpp providing deterministic_rng(seed) and helper to build small grids. Refactor existing tests to use it. Return patch.

Prompt 13:
Add coverage build option (ENABLE_COVERAGE). For GCC/Clang add -O0 -g --coverage (or -fprofile-arcs -ftest-coverage). Update ENGINEERING_PLAN.md with coverage run instructions (gcovr/llvm-cov example). Return patch.

---

## Phase 3 – C++23 Adoption

Prompt 14:
Produce a dependency order chart mapping: std::expected, std::print, std::ranges (planner loops), std::mdspan (kinematics), std::jthread (control loop). Include prerequisites per feature. No code yet.

Prompt 15:
Add CMake option ROBOKIT_USE_CPP23=ON to switch CMAKE_CXX_STANDARD=23 and define ROBOKIT_CPP23. Return patch.

Prompt 16:
Refactor Result usage to conditional typedef: if ROBOKIT_CPP23 then std::expected else custom Result. Adjust planner + (later) config. Return patch + updated tests (unchanged semantics).

Prompt 17:
Introduce std::print for logging under ROBOKIT_CPP23, fallback to existing iostream path. Return patch.

Prompt 18:
Refactor planner neighbor iteration using std::ranges/views (transform/filter) under C++23 macro. Keep identical functional behavior. Return patch.

Prompt 19:
Prototype mdspan usage in kinematics (matrix view for Jacobian). No algorithmic improvement yet; add TODO(CPP23) for future optimizations. Add numeric parity test comparing old vs new path. Return patch.

Prompt 20:
Migrate control loop to std::jthread + std::stop_token (guarded by ROBOKIT_CPP23). Provide test exercising start/stop. Return patch.

---

## Phase 4 – MISRA & Security Hardening

Prompt 21:
Create MISRA_GAP_ANALYSIS.md listing anticipated violated rule categories (resource management, dynamic allocation, unspecified behavior, exceptions usage if any). Map each to affected files.

Prompt 22:
Create MISRA_DEVIATIONS.md template: columns Rule | Status (Planned / Permanent) | Justification | Mitigation. Populate initial entries.

Prompt 23:
Add SECURITY_MODEL.md: assets (config file, sensor inputs, planner map), threats (malformed input, integer overflow, predictable RNG, denial-of-service via large grid), trust boundaries, initial mitigations.

Prompt 24:
Harden config parsing: bounded line length, reject non-printable characters, clamp numeric values, explicit error codes via Result or std::expected. Add negative tests (oversized line, bad key, value overflow). Return patch.

Prompt 25:
Add planner input validation: non-zero dimensions, upper dimension limit, start/goal bounds, cell occupancy validation. Add corresponding failure tests. Return patch.

Prompt 26:
Centralize RNG seeding in rng.hpp with function secureish_seed(mode) (mode: deterministic|time). Add TODO(SEC) for cryptographic source. Refactor sensors/tests accordingly. Return patch.

Prompt 27:
Eliminate any remaining raw new/delete (confirm none or patch). Update INITIAL_RISK_BASELINE.md with new counts.

Prompt 28:
Introduce .clang-tidy and .cppcheck-suppress (minimal) plus update ENGINEERING_PLAN.md with invocation instructions. Return patch.

Prompt 29:
Sweep for unsafe C functions (strcpy, sprintf, atoi). Replace with safer std:: variants or explicit parsing. Return patch or confirmation.

Prompt 30:
Add explicit narrow casts using static_cast and (if needed) checked helpers. Insert TODO(MISRA) where potential truncation remains. Provide patch.

---

## Phase 5 – Advanced Testing & Full Coverage

Prompt 31:
Generate TEST_INVENTORY.md: list each public function → Status (Not / Partial / Full). No code.

Prompt 32:
Enumerate branch coverage plan: for planner, config, kinematics, control loop error paths. Provide table Condition | Test Case Name. No code.

Prompt 33:
Add property-based style tests (repeat randomized joint inputs; forward→inverse→forward ≈ original within tolerance). Document tolerance in comments. Return patch.

Prompt 34:
Add negative and edge tests: zero-length arm segment, empty sensor list behavior, unreachable planner states. Return patch.

Prompt 35:
Introduce test-only fault injection hooks (#ifdef ROBOKIT_TESTING) in sensor read & config load to simulate failures. Add tests invoking them. Return patch.

Prompt 36:
Request coverage report summary (user runs tooling). Provide assistant plan for remaining uncovered lines with micro-test suggestions. (Assistant response only; no patch.)

Prompt 37:
Implement micro-tests closing remaining uncovered lines (avoid meaningless assertions). Return patch.

Prompt 38:
Add mutation testing plan section to ENGINEERING_PLAN.md (tool: Mull or equivalent, target modules, exclusion list). Return patch.

Prompt 39:
Add soft coverage gate: script or CTest custom command failing below 90% line coverage (configurable COVERAGE_MIN). Return patch.

Prompt 40:
Raise coverage gate to 100% (or justify exclusions listing file:line + rationale). Update ENGINEERING_PLAN.md coverage section. Return patch.

---

## Phase 6 – Concurrency & Performance (Optional)

Prompt 41:
Introduce message_queue.hpp (simple thread-safe queue) + TODO(PERF) for lock-free future. No integration yet. Return file.

Prompt 42:
Refactor control loop to optional multi-thread mode: sensor thread, planner thread, main loop aggregator (guarded by build option). Provide patch + tests.

Prompt 43:
Add microbenchmark (benchmark_planner.cpp) with grid scaling; record timing summary to stdout. Guard by BUILD_BENCH. Return patch.

Prompt 44:
Add PERFORMANCE_NOTES.md documenting baseline vs ranges vs mdspan planner timings (user fills numbers). Provide template file.

---

## Consolidation & Release

Prompt 45:
List all remaining TODO(CPP23), TODO(SEC), TODO(MISRA), TODO(TEST), TODO(PERF) with classification: Done / Next / Defer. Produce table.

Prompt 46:
Generate RELEASE_NOTES.md draft summarizing evolution (Phase 1 → Phase 6) with major changes and breaking interface notes.

Prompt 47:
Produce final RISK_SNAPSHOT.md: residual risks (non-real-time, simplified physics, educational error models).

Prompt 48:
Update ENGINEERING_PLAN.md metrics section with final counts (test files, LOC, coverage %, deviations accepted, security checks implemented). Return patch.

Prompt 49:
Create a final VALIDATION_SCRIPT.skel (shell + batch outline) listing: configure, build (Debug + Release), run tests, run coverage, run static analysis, summarize warnings. Return skeleton file only.

Prompt 50:
Assistant review request: Audit for any public API lacking tests, any untagged risky patterns, and any lingering dynamic allocations.

---

## MISRA & Security Prompt Guidance

When implementing MISRA-related prompts:
- Avoid speculative rule numbers if uncertain; label as “Likely Rule Category”.
- Justify deviations (performance, educational clarity, controlled environment).
- Prefer explicit casts and initialization of all members.
- Avoid new global mutable state—wrap in function static if unavoidable and tag TODO(MISRA).

When implementing Security prompts:
- Always validate size and range before allocation or indexing.
- Fail fast with explicit error return (no silent fallbacks).
- Tag each newly added validation with TODO(SEC) removal note after test coverage confirmed.

---

## Test Quality Guidance

A test is insufficient if:
- It only asserts construction succeeds without behavioral check.
- It mirrors implementation logic (duplicating the same algorithm).
- It relies on time sleeping without deterministic control (replace with hooks).

Aim for:
- Behavioral invariants (e.g., path endpoints correct, kinematics round-trip).
- Edge + negative paths (invalid input handled explicitly).
- Deterministic randomization via seeded utilities.

---

## Coverage Strategy

Priority to cover:
1. All error returns (planner/config).
2. All branches of validation guards.
3. Sensor fault injection pathways.
4. Kinematics singular conditions (if stubbed, justify).

Document any excluded lines in ENGINEERING_PLAN.md (table: File | Line | Reason).

---

## Completion Criteria

You are “done” when:
- ROBOKIT_USE_CPP23=ON builds cleanly with all tests passing.
- Coverage gate at 100% passes without unjustified exclusions.
- MISRA_DEVIATIONS.md and SECURITY_MODEL.md are current.
- All TODO tags categorized (none orphaned).
- Release notes draft ready.

---