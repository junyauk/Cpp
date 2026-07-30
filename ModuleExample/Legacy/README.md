# Legacy Project

## Overview

`Legacy` contains the original (pre-modernization) APIs and types that are consumed by other projects in this solution. It provides simple numeric operations and a small, class-based calculator interface intended to represent legacy code that is adapted or wrapped by modern modules.

## Purpose

- Represent a legacy code surface used for migration and interoperability examples.
- Provide stable, simple APIs that other modules (`ModuleA`, `ModuleB`, `Caller`) call directly or via adapters.
- Serve as a clear contrast between legacy-style APIs and C++20 module-based code in the solution.

## Public API (summary)

Namespace: `moduleexample::legacy`

- Free functions:
  - `int legacy_add(int a, int b);` — basic addition function.

- Constants:
  - `constexpr int kLegacyValue = 500;` — example legacy constant.

- Classes:
  - `class LegacyCalculator`
    - `LegacyCalculator() = default;`
    - `int multiply(int a, int b);` — instance method for multiplication.
    - `static std::string info();` — static informational string about the legacy calculator.

## Dependencies (within this solution)

- Consumed by: `Caller`, `ModuleA`/`ModuleB` adapters (via adapter functions), and unit tests in `ModulesTest`.
- No external third-party dependencies.

## Build and Tooling Notes

- The code is simple header/implementation style; ensure the project is included in the `ModuleExample` solution and built before consumers.
- The solution is configured for a C++20-capable toolchain. Consumers may import or include `Legacy` as appropriate for the project's module vs header configuration.
- No special build steps or external tooling are required for `Legacy` itself.

## C++ features used

- Namespaces (`moduleexample::legacy`).
- `constexpr` for compile-time constant (`kLegacyValue`).
- Classes with defaulted constructor (`LegacyCalculator()`).
- Static member functions (`LegacyCalculator::info()`).
- Standard library strings (`std::string`).
- Plain free functions and simple POD-like usage.

## Testing

- Unit tests that exercise `Legacy` behavior or its adapters exist in the `ModulesTest` project. Build the solution and run the test project to validate behavior.

## Notes

- This project intentionally keeps the API surface minimal to illustrate legacy-to-module/adapter interactions.
- No external links or documentation references are required in this README.