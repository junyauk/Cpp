# 00_ConceptsTest

## Overview

This project contains unit tests for the `00_Concepts` examples. Tests exercise C++20 Concepts usage, compile-time constraints, and overload resolution behavior demonstrated in `Concepts_Basic.h`.

## Requirements

- Visual Studio 2022 (recommended) or another C++20-capable toolchain.
- GoogleTest is used by the test project (NuGet package included in the solution `packages/` folder).

## Build

1. Open `C++20Features.sln` in Visual Studio.
2. Ensure the C++ language standard is set to C++20 for the solution or the test project.
3. Build `00_ConceptsTest` (or build the full solution). NuGet packages should be restored automatically if required.

## Running tests

- Run tests from Visual Studio Test Explorer.
- Alternatively, run the generated test executable from the test project's output directory (Debug/Release).

## What the tests cover

The test suite verifies:
- Correct behavior of concept-constrained functions (e.g., `isGreaterThan`, `areEqual`).
- Proper SFINAE-like selection / overload resolution driven by concepts (integral vs floating-point vs fallback).
- Requirements-based constraints such as presence of `container.empty()` via constrained templates.
- Compile-time safety and intended diagnostics when passing unsupported types.

## Notable files

- `00_ConceptsTest.vcxproj` — Visual Studio project file for tests.
- `00_ConceptsTest_Basic.cpp`, `00_ConceptsTest_Advance.cpp` — test sources using GoogleTest.
- `pch.h` / `pch.cpp` — precompiled header support.

## Contributing

- Add tests that are small, focused, and clearly validate a single behavior.
- When adding new examples in `00_Concepts`, include corresponding unit tests here.
- Keep tests deterministic and avoid relying on external state.

## License

No license file is included by default. Add a `LICENSE` file if you intend to publish or share the repository.