# 04_ConcurrencyTest

## Overview

This project contains unit tests for the `04_Concurrency` examples. Tests exercise cooperative cancellation, thread lifecycle, and synchronization primitives introduced or improved in C++20.

## Requirements

- C++20-capable compiler (Visual Studio 2022 recommended).
- GoogleTest framework (NuGet package included under `packages/` in the solution).

## Build

1. Open `C++20Features.sln` in Visual Studio 2022.  
2. Ensure the C++ Language Standard is set to C++20 (Project Properties → C/C++ → __Language__ → __C++ Language Standard__).  
3. Build the `04_ConcurrencyTest` project or the entire solution. NuGet packages should be restored automatically if required.

## Contents

- `04_ConcurrencyTest.vcxproj` — Visual Studio project file for tests.
- `04_ConcurrencyTest.cpp` — GoogleTest-based tests covering:
  - `std::jthread` and cooperative cancellation via `std::stop_token`.
  - `std::latch` usage for one-shot synchronization scenarios.
  - `std::barrier` usage for multi-phase synchronization.
  - Atomic state updates and basic thread coordination checks.
- `pch.h` / `pch.cpp` — precompiled header support.

## Running tests

- Run tests from Visual Studio Test Explorer.
- Alternatively, run the produced test executable from the test project's output directory (Debug/Release).

## Test guidance

- Prefer deterministic synchronization patterns to avoid flaky timing-based failures.
- Keep tests short and focused on observable behavior (state transitions, synchronization outcomes, cancellation handling).
- Avoid relying on long sleeps; use small timeouts only when necessary and document their purpose.

## Contributing

- Add concise, focused tests for any new concurrency examples or behavioral changes.
- Ensure tests are deterministic and document any timing assumptions.
- When adding tests that exercise multi-threaded behavior, assert observable outcomes rather than exact timings.

## License

No license file is included by default. Add a `LICENSE` file if you intend to publish or share the repository.