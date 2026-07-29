# 06_JthreadStopToken

This project demonstrates C++20 thread management and cooperative cancellation using `std::jthread` and the stop token API. The examples provide compact classes and utilities that show how to start, request cancellation, and cleanly stop worker threads and thread pools using modern C++ synchronization primitives.

## Contents

- `06_JthreadStopToken.h` / `06_JthreadStopToken.cpp` — Implementations include:
  - `Worker` — simple RAII `std::jthread` that prints progress and exits when a stop is requested.
  - `Worker2` — named worker demonstrating starting a `std::jthread`, requesting stop, and clean teardown with logging.
  - `Worker3` — atomic state and counter example showing start/stop semantics with `std::jthread` and `std::stop_token`.
  - `Worker4` — worker that accepts an external `std::stop_token` and a data vector; demonstrates cooperative early exit and aggregation of results.
  - `Worker5` — demonstrates passing a `std::stop_token` into a long-running loop and exposing a running flag.
  - `ThreadPool` — a thread pool implemented with `std::jthread`, `std::condition_variable_any` (used with a stop token-aware wait predicate), a task queue, and cooperative stopping via `request_stop` on each worker thread.
  - `WorkerPool` — manages multiple `std::jthread` workers using a `std::stop_source` to broadcast stop requests to all workers.

## C++20 features used

- `std::jthread` — joinable threads with automatic joining in destructors and integrated stop tokens.
- `std::stop_token`, `std::stop_source` — cooperative cancellation primitives to request and detect stop conditions.
- `std::jthread::request_stop()` and `stop_requested()` — requesting and observing cancellation.
- `std::condition_variable_any::wait(lock, stop_token, predicate)` — stop-token-aware waiting that can be unblocked by a stop request.
- Thread-safe atomics (`std::atomic`) for lightweight thread coordination.
- Use of lambda thread entry points that accept `std::stop_token` parameters.
- Modern RAII idioms for thread lifecycle management.

## Requirements

- C++20 compatible compiler and standard library with support for `std::jthread` and the stop token API.

## Testing

- Unit tests for this project are located in the sibling test project `06_JthreadStopTokenTest`. The tests exercise start/stop behavior, cooperative cancellation, and thread-pool shutdown semantics.

## Notes

- Examples demonstrate cooperative cancellation; worker loops should periodically check the stop token to ensure prompt shutdown.
- `std::condition_variable_any` is used in the thread pool to allow waiting with a `std::stop_token` predicate; this is a recommended pattern for stop-token-aware wait semantics.
- No usage examples are included in this README. Refer to the test project to observe concrete behaviors and lifecycle scenarios.