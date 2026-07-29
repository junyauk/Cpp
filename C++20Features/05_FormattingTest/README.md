# 05_FormattingTest

## Overview

This project contains unit tests for the `05_Formatting` examples. Tests validate `std::format` usage, numeric and alignment formatting, and chrono/time formatting behaviors across supported platforms.

## Requirements

- C++20-capable compiler (Visual Studio 2022 recommended).
- GoogleTest framework (NuGet package included in the solution under `packages/`).

## Build

1. Open `C++20Features.sln` in Visual Studio 2022.
2. Ensure the C++ Language Standard is set to C++20 (Project Properties → C/C++ → __Language__).
3. Build the `05_FormattingTest` project or the entire solution. NuGet packages should be restored automatically if required.

## Contents

- `05_FormattingTest.vcxproj` — Visual Studio project file for the tests.
- Test sources (e.g., `05_FormattingTest.cpp`) — GoogleTest-based tests that assert formatting outputs, numeric formatting behavior, padding/alignment, and chrono formatting correctness.
- `pch.h` / `pch.cpp` — Precompiled header support.

## Running tests

- Run tests from Visual Studio Test Explorer.
- Alternatively, execute the produced test binary from the test project's output directory (Debug/Release).

## Contributing

- Add focused tests that validate a single formatting behavior or edge case.
- When changing formatting utilities, update or add unit tests to cover regressions.

## License

No license file is included by default. Add a `LICENSE` file if publishing or sharing the repository.