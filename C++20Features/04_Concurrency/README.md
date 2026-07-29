# 04_Concurrency

## Overview

This project demonstrates C++20 concurrency primitives and synchronization utilities through compact, focused examples. It highlights cooperative cancellation with `std::jthread` / `std::stop_token`, one-shot synchronization with `std::latch`, and multi-phase synchronization with `std::barrier`.

## Requirements

- C++20-capable compiler (Visual Studio 2022 recommended).
- Project configured to use the C++20 language standard.

## Build

1. Open `C++20Features.sln` in Visual Studio 2022.  
2. Ensure the C++ Language Standard is set to C++20 (Project Properties → C/C++ → __Language__ → __C++ Language Standard__).  
3. Build the `04_Concurrency` project or the entire solution.

Precompiled headers (`pch.*`) are provided and used by the project.

## Contents

- `Concurrency_Basic.h`  
  - `Concurrency_Basic::ConcurrencyBasic` class demonstrating:
    - `void longRunningTask(std::stop_token token)` — cooperative cancellation via `std::stop_token`.
    - `int runAndStopThread(int durationMs)` — starts a `std::jthread`, requests stop, returns iteration count.
    - `void barrierTask(std::latch& l, int id, std::atomic<int>& result)` and `int runLatchSynchronization(int numWorkers)` — examples using `std::latch`.
    - `void barrierPhaseTask(std::barrier<>& b, int id, std::atomic<int>& result)` and `int runBarrierSynchronization(int numWorkers)` — multi-phase synchronization with `std::barrier`.
  - Uses `std::atomic` for shared-state updates and demonstrates RAII thread management with `std::jthread`.

- `04_Concurrency.vcxproj` — Visual Studio project file.
- `pch.h` / `pch.cpp` — precompiled header support.

## Tests

- `04_ConcurrencyTest` contains GoogleTest-based unit tests that exercise thread lifecycle, stop requests, latch and barrier synchronization scenarios.
- Run tests via Visual Studio Test Explorer or execute the test binary produced in the test project's output folder.

## Contributing

- Keep examples small and deterministic.
- Add unit tests for new behaviors or edge cases.
- Avoid long-running tests or non-deterministic timing dependencies; prefer deterministic synchronization patterns for CI.

## License

No license file is included by default. Add a `LICENSE` file if you intend to publish or share the repository.