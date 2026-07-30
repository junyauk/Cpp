# ModuleExample Solution

## Overview

`ModuleExample` is a small C++20 sample solution demonstrating modern C++ module usage alongside a legacy codebase. The solution contains multiple projects that illustrate module interfaces, template exports, adapters to legacy code, and a thin wrapper layer used by unit tests.

## Projects in this solution

- `Caller` — Wrapper and adapter layer that consumes modules and legacy APIs; exposes a compact namespaced free-function API used by tests.
- `Legacy` — Minimal legacy-style API (free functions, constants, and a small class) used to demonstrate adaptation.
- `MiniModules` — Small, focused modules providing basic utilities (hello message, simple math, and string helpers) used by callers and tests.
- `Modules` — Core C++20 modules including `ModuleA`, `ModuleB`, and `ModuleT` (templates and utilities); modules may import `Legacy` and export functions, classes, constants, and templates.
- `ModulesTest` — Google Test-based unit tests that validate module behavior and the `Caller` surface.

## Purpose and goals

- Show practical composition of C++20 modules and legacy code within a single solution.
- Demonstrate template exports, explicit instantiation, and module-level APIs.
- Provide clear unit tests that validate inter-module integration and adapter behavior.

## Build prerequisites

- Visual Studio 2022 (or later) with C++ development workload and C++20 module support enabled.
- No external libraries are required except the Google Test framework included in the test project.

## Build and run

1. Open the solution `ModuleExample.sln` in Visual Studio 2022.
2. Restore and ensure the Google Test project configuration is available (built-in in the solution).
3. Build the entire solution (Build > Build Solution).
4. Run unit tests:
   - Use __Test Explorer__ in Visual Studio to run and inspect Google Test results, or
   - Execute the `ModulesTest` test binary from the test project's output directory.

Notes:
- Module projects use `.ixx` interface units and corresponding implementation units. Ensure project references and module import paths are intact in the solution so imported modules resolve correctly.
- Some translation units (e.g. `Caller`) use a precompiled header `pch.h` — ensure the project configuration matches the provided files.

## C++ features used across the solution

- C++20 modules (`export module ...;` and `import ...;`).
- Exported and imported templates, explicit template instantiation.
- Template specialization (e.g. `NumberBox<std::string>` specialization).
- Namespaces (nested namespaces such as `moduleexample::modulea`).
- `constexpr` constants and inter-module constant composition.
- Classes with instance and static members, defaulted constructors.
- `std::unique_ptr`, runtime polymorphism via abstract interfaces.
- Standard library usage: `std::string`, streams (`std::ostringstream`), `<cmath>` utilities.
- Google Test framework for unit testing, including parameterized tests.

## Testing

- Unit tests live in the `ModulesTest` project and exercise the `Caller` API and underlying modules.
- Run tests after building the solution to validate behavior.

## Notes

- No external links or third-party network resources are required by this repository.
- The sample code focuses on clarity and demonstration of C++20 module capabilities and interoperability with legacy code.