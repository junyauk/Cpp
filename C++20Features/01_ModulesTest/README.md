# 01_ModulesTest

## Overview

`01_ModulesTest` contains unit tests for the `01_ModulesApp` module examples. Tests validate module interfaces, integration points, and expected behaviors of the reusable components provided by the `01_ModulesApp` project.

## Requirements

- C++20-capable compiler (Visual Studio 2022 recommended).
- GoogleTest framework (NuGet package is included in the solution under `packages/`).

## Build

1. Open `C++20Features.sln` in Visual Studio 2022.  
2. Ensure the C++ Language Standard is set to C++20 (Project Properties → C/C++ → __Language__ → __C++ Language Standard__).  
3. Build the `01_ModulesTest` project or the entire solution. NuGet packages should be restored automatically if required.

Precompiled headers (`pch.*`) are provided and used by the project.

## Contents

- `01_ModulesTest.vcxproj` — Visual Studio project file for tests.
- Test sources (e.g., `01_ModulesTest.cpp`) — GoogleTest-based unit tests targeting `01_ModulesApp` components.
- `pch.h` / `pch.cpp` — Precompiled header support.

## Test scope

The test suite focuses on:
- Verifying public module interfaces and their contract.
- Integration checks between module components where applicable.
- Edge cases and deterministic behavior for functions exposed by `01_ModulesApp`.
- Ensuring no regressions for refactoring of module internals.

## Running tests

- Use Visual Studio Test Explorer to run and inspect tests.
- Alternatively, run the test executable produced in the test project's output directory (Debug/Release).

## Contributing

- Add focused unit tests that validate a single behavior or contract.
- When modifying public interfaces in `01_ModulesApp`, update or add tests here to cover changes.
- Keep tests deterministic and avoid external dependencies where possible.

## License

No license file is included by default. Add a `LICENSE` file if you intend to publish or share the repository.