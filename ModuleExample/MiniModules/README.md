# MiniModules

## Overview

`MiniModules` contains a set of small, focused C++20 modules that provide simple utilities used elsewhere in the `ModuleExample` solution. The modules are intentionally minimal to demonstrate module-based organization and to be consumable by the `Caller` project and unit tests.

## Purpose

- Provide lightweight, single-responsibility modules for example purposes.
- Demonstrate C++20 module usage and how small modules are consumed by higher-level code.
- Supply utility functionality exercised by the `ModulesTest` project (via `Caller` wrappers).

## Public API (summary)

The project is organized into small module surfaces (examples inferred from tests and project wrappers):

- Hello module
  - Prints or returns an identifying message such as `"Hello from MiniModules!"`.
  - Example consumer function name (via `Caller`): `CallHello()`.

- Math module
  - Basic numeric utilities:
    - `computeSquare(double)` — returns the square of a value.
    - `computeHypotenuse(double, double)` — returns the euclidean hypotenuse for two sides.
  - These functions are exercised by unit tests and exposed to callers (wrapped by `Caller::` functions in the solution).

- String utilities module
  - Simple string transformations:
    - `to_upper(std::string)` — converts ASCII characters to upper case.
    - `to_lower(std::string)` — converts ASCII characters to lower case.
  - Test wrappers reference these via symbols such as `caller_to_upper` and `caller_to_lower`.

Note: The test project references these capabilities through wrapper headers in the `Caller` project; the modules themselves provide the implementations consumed by those wrappers.

## Dependencies (within this solution)

- Consumed by: `Caller` (wrapper layer) and `ModulesTest` (via `Caller` wrappers).
- No external third-party dependencies are required.

## Build and Tooling Notes

- Requires a C++20-capable toolchain (project configured to compile modules).
- Built as part of the `ModuleExample` solution; ensure `MiniModules` project is included and built before consumers.
- No special external tooling or runtime configuration is necessary.

## C++ features used

- C++20 modules (module partitions / top-level modules).
- Namespaces and free functions.
- Standard library strings (`std::string`) and basic stream/character utilities.
- Numeric utilities from `<cmath>` for hypotenuse/square computations.
- Inter-module composition: functions consumed by higher-level wrappers in `Caller`.
- Simple, focused API surfaces suitable for unit testing.

## Testing

- Unit tests that verify `MiniModules` behavior are present in the `ModulesTest` project; tests access these capabilities through `Caller` wrappers. Build the solution and run the `ModulesTest` suite to validate behavior.

## Notes

- README focuses on the module responsibilities and the observable API surface used by the rest of the solution.
- No external links or third-party references are included.