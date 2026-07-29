# 06_ThreeWayCompTest

## Overview

This project contains unit tests for the `06_ThreeWayComp` examples. Tests validate comparison semantics produced by defaulted three-way comparison (`operator<=>`) and auto-generated equality operators.

## Requirements

- C++20-capable compiler (Visual Studio 2022 recommended).
- GoogleTest framework (NuGet package included in the solution under `packages/`).

## Build

1. Open `C++20Features.sln` in Visual Studio 2022.
2. Ensure the C++ Language Standard is set to C++20 (Project Properties → C/C++ → __Language__).
3. Build the `06_ThreeWayCompTest` project or the entire solution. NuGet packages should be restored automatically if required.

## Contents

- `06_ThreeWayCompTest.vcxproj` — Visual Studio project file for the tests.
- Test sources (e.g., `06_ThreeWayCompTest.cpp`) — GoogleTest-based tests that assert comparison behavior, ordering, and equality semantics.
- `pch.h` / `pch.cpp` — Precompiled header support.

## Running tests

- Run tests from Visual Studio Test Explorer.
- Alternatively, execute the produced test binary from the test project's output directory (Debug/Release).

## Test scope

The test suite focuses on:
- Correct ordering semantics (less, greater, equivalent) using the defaulted `<=>` operator.
- Auto-generated `operator==` behavior.
- Edge cases for partial vs total ordering where appropriate.

## Contributing

- Add focused tests validating a single comparison scenario or edge case.
- When modifying struct members or comparison categories, update tests accordingly.
- Keep tests deterministic and avoid reliance on external state.

## License

No license file is included by default. Add a `LICENSE` file if you intend to publish or share the repository.