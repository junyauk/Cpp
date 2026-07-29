# 02_RangesTest

## Overview

This project contains unit tests for the `02_Ranges` examples. Tests exercise behavior of range-based pipelines, views, and ranges-aware algorithms to ensure correctness and illustrate intended usage.

## Requirements

- C++20-capable compiler (Visual Studio 2022 recommended).
- GoogleTest framework (NuGet package included in the solution under `packages/`).

## Build

1. Open `C++20Features.sln` in Visual Studio 2022.  
2. Ensure the C++ Language Standard is set to C++20 (Project Properties → C/C++ → __Language__ → __C++ Language Standard__).  
3. Build the `02_RangesTest` project or build the entire solution.

Precompiled headers (`pch.*`) are provided and used by the project.

## Contents

- `02_RangesTest.vcxproj` — Visual Studio project file for the test project.
- `02_RangesTest.cpp` — GoogleTest-based tests covering:
  - Filtering and transformation pipeline validation.
  - Counting occurrences via `std::ranges::count`.
  - Summation of a subrange using `std::views::take` combined with algorithms.
  - Behavior on empty input (view laziness).

- `pch.h` / `pch.cpp` — precompiled header support.

## Running tests

- Run tests from Visual Studio Test Explorer.
- Alternatively, run the test executable located in the test project's output directory (Debug/Release).

## Contributing

- Add focused unit tests that validate a single behavior.
- When extending `02_Ranges` examples, add or update tests here to cover new behavior.
- Keep tests deterministic and avoid external dependencies.

## License

No license file is included by default. Add a `LICENSE` file if you intend to publish or share the repository.