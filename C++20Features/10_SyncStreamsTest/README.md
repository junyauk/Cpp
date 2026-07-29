# 10_SyncStreamsTest

## Overview

This project contains unit tests for the `10_SyncStreams` examples. Tests verify synchronized output behavior using `std::osyncstream`, ensuring thread-safe captured output and demonstrating safe vs unsafe printing scenarios.

## Requirements

- C++20-capable compiler (Visual Studio 2022 recommended).
- Standard library with `<syncstream>` support.
- GoogleTest framework (NuGet package included in the solution under `packages/`).

## Build

1. Open `C++20Features.sln` in Visual Studio 2022.
2. Ensure the C++ Language Standard is set to C++20 (Project Properties → C/C++ → __Language__).
3. Build the `10_SyncStreamsTest` project or the entire solution. NuGet packages should be restored automatically if required.

## Contents

- `10_SyncStreamsTest.vcxproj` — Visual Studio project file for the tests.
- Test sources (e.g., `10_SyncStreamsTest.cpp`) — GoogleTest-based tests capturing and asserting synchronized output produced by `SyncStreams_Basic::SyncStreamsBasic`.
- `pch.h` / `pch.cpp` — Precompiled header support.

## Running tests

- Run tests from Visual Studio Test Explorer.
- Alternatively, execute the produced test binary from the test project's output directory (Debug/Release).

## Test scope

The test suite focuses on:
- Verifying that `std::osyncstream` produces atomic per-thread output blocks.
- Detecting interleaving or corruption in unsafe prints vs consistent output in synchronized prints.
- Assertions on captured output content and ordering rather than timing.

## Contributing

- Add focused, deterministic tests that validate single behaviors or edge cases.
- Avoid tests that rely on thread scheduling timing; prefer assertions on captured output structure.
- Document any environment-specific assumptions (line endings, encoding) in test code.

## License

No license file is included by default. Add a `LICENSE` file if you intend to publish or share the repository.