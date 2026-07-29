# 06_JthreadStopTokenTest

This test project contains GoogleTest unit tests that validate the thread management and cooperative cancellation examples in the sibling `06_JthreadStopToken` project. The tests exercise lifecycle, cooperative stop requests, thread-pool behavior, and stdout-observable events.

## Contents

- `06_JthreadStopTokenTest.cpp` — GoogleTest cases covering:
  - Basic `Worker` lifecycle and explicit/RAII stop behavior.
  - `Worker2` explicit stop and destructor-based stop semantics.
  - `Worker3` start/stop semantics, atomic running flag and counter verification.
  - `Worker4` cooperative cancellation via an external `std::stop_token`, joining and partial work detection (compares results against `std::accumulate`).
  - `Worker5` use of shared `std::stop_token` across multiple workers, start/join and running state assertions.
  - `ThreadPool` tests:
    - Single task execution and multiple-task execution.
    - Parallel task execution verification.
    - Destructor-triggered shutdown behavior and task completion assertions.
    - Multiple queued tasks observed via captured stdout and explicit `stop()` calls.

## Test utilities

- Tests use `testing::internal::CaptureStdout()` to capture and assert on printed output for worker lifecycle messages.

## Test framework

- GoogleTest is used for all unit tests. Ensure the test runner links and runs GoogleTest to execute these cases.

## C++ features used in the test project

- `std::jthread`, `std::stop_token`, `std::stop_source` — thread lifecycle and cooperative cancellation primitives.
- `std::condition_variable_any` with stop-token-aware waiting (exercised by the thread-pool implementation under test).
- `std::atomic` for lightweight synchronization and state tracking.
- Container and ownership utilities — `std::vector`, `std::unique_ptr`.
- Thread utilities — `std::this_thread::sleep_for`.
- Standard algorithms/utilities — `std::accumulate`.
- GoogleTest macros and helpers (`TEST`, `EXPECT_EQ`, `EXPECT_TRUE`, `SUCCEED`) and internal stdout capture helpers.

## Requirements

- C++20 compatible compiler and standard library with support for `std::jthread` and the stop token API.
- GoogleTest linked into the test runner.

## Notes

- Tests assert both functional outcomes (counters, results) and observable lifecycle messages printed to stdout.
- No usage examples are included in this README; run the test suite to observe concrete behaviors and expected outputs.