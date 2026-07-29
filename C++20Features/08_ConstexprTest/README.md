# 08_ConstexprTest

## Overview

This project contains unit tests for the `08_Constexpr` examples. Tests validate constexpr functions, compile-time evaluation semantics, and runtime equivalence where applicable.

## Requirements

- C++20-capable compiler (Visual Studio 2022 recommended).
- GoogleTest framework (NuGet package included in the solution under `packages/`).

## Build

1. Open `C++20Features.sln` in Visual Studio 2022.
2. Ensure the C++ Language Standard is set to C++20 (Project Properties → C/C++ → __Language__).
3. Build the `08_ConstexprTest` project or the entire solution. NuGet packages should be restored automatically when needed.

## Contents

- `08_ConstexprTest.vcxproj` — Visual Studio project file for the tests.
- Test sources (e.g., `08_ConstexprTest.cpp`) — GoogleTest-based tests that assert compile-time evaluation behavior and runtime results.
- `pch.h` / `pch.cpp` — Precompiled header support.

## Running tests

- Run tests from Visual Studio Test Explorer.
- Alternatively, execute the produced test binary from the test project's output directory (Debug/Release).

## Test scope

The test suite focuses on:
- Verifying functions that can be evaluated at compile time using `constexpr`.
- Ensuring runtime behavior matches compile-time expectations where applicable.
- Edge cases and deterministic behavior for compile-time computations.

## Contributing

- Add concise tests that validate a single constexpr behavior or edge case.
- When adding new constexpr utilities, include tests that demonstrate compile-time evaluation where possible.
- Keep tests deterministic and well-documented.

## License

No license file is included by default. Add a `LICENSE` file if you intend to publish or share the repository.