# 09_AtomicWaitTest

## Overview

This project contains unit tests for the `09_AtomicWait` examples. Tests validate `std::atomic::wait`/`notify_one` usage, producer/consumer coordination, and notification semantics under C++20.

## Requirements

- C++20-capable compiler (Visual Studio 2022 recommended).
- GoogleTest framework (NuGet package included in the solution under `packages/`).

## Build

1. Open `C++20Features.sln` in Visual Studio 2022.
2. Ensure the C++ Language Standard is set to C++20 (Project Properties → C/C++ → __Language__).
3. Build the `09_AtomicWaitTest` project or the entire solution. NuGet packages should be restored automatically if required.

## Contents

- `09_AtomicWaitTest.vcxproj` — Visual Studio project file for the tests.
- Test sources (e.g., `09_AtomicWaitTest.cpp`) — GoogleTest-based tests that exercise producer/consumer coordination and atomic notification semantics.
- `pch.h` / `pch.cpp` — Precompiled header support.

## Running tests

- Run tests from Visual Studio Test Explorer.
- Alternatively, execute the produced test binary from the test project's output directory (Debug/Release).

## Test scope

The test suite focuses on:
- Correct notification and wake-up behavior using `std::atomic::wait` and `notify_one`.
- Producer/consumer ordering and final state validation.
- Handling spurious wake-ups and deterministic synchronization assertions.

## Contributing

- Add focused, deterministic tests for new synchronization scenarios.
- Avoid long sleep-based timing assumptions; prefer observable state assertions after synchronization.
- Document any timing or platform-specific assumptions in test code.

## License

No license file is included by default. Add a `LICENSE` file if you intend to publish or share the repository.