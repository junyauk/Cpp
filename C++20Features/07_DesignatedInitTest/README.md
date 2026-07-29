# 07_DesignatedInitTest

## Overview

This project contains unit tests for the `07_DesignatedInit` examples. Tests verify correct usage of designated initializers, ordering constraints, and expected behaviors for partial and full aggregate initialization.

## Requirements

- C++20-capable compiler (Visual Studio 2022 recommended).
- GoogleTest framework (NuGet package included in the solution under `packages/`).

## Build

1. Open `C++20Features.sln` in Visual Studio 2022.
2. Ensure the C++ Language Standard is set to C++20 (Project Properties → C/C++ → __Language__).
3. Build the `07_DesignatedInitTest` project or the entire solution. NuGet packages should be restored automatically if required.

## Contents

- `07_DesignatedInitTest.vcxproj` — Visual Studio project file for the tests.
- Test sources (e.g., `07_DesignatedInitTest.cpp`) — GoogleTest-based tests that validate designated initializer behaviors, compile-time ordering rules (documented), and runtime-validated aggregate initialization results.
- `pch.h` / `pch.cpp` — Precompiled header support.

## Running tests

- Run tests from Visual Studio Test Explorer.
- Alternatively, execute the test binary produced in the test project's output directory (Debug/Release).

## Test scope

The test suite focuses on:
- Full and partial designated initialization behavior.
- Compiler-enforced ordering rules for designated initializers.
- Documented compile-time failure cases (kept as commented references in test code where applicable).

## Contributing

- Add concise tests that validate a single initialization pattern or compiler constraint.
- When adding new examples in `07_DesignatedInit`, include corresponding unit tests here.
- Keep tests deterministic and well-documented.

## License

No license file is included by default. Add a `LICENSE` file if you intend to publish or share the repository.