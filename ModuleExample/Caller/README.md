# Caller Project

## Overview

`Caller` is a small bridge layer that demonstrates how to consume functionality exposed by other modules and the legacy codebase inside this solution. It exposes a compact C-style API (namespaced free functions) and a few small types that call into `ModuleA`, `ModuleB`, `Legacy`, and `ModuleT`.

## Purpose

- Provide an example of calling into C++20 modules and legacy code from the same translation unit.
- Centralize calls that combine results from multiple modules or adapt legacy APIs for modern usage.
- Offer a minimal surface for tests in the `ModulesTest` project.

## Public API (summary)

The primary namespace is `moduleexample::caller`.

- Basic wrappers around `ModuleA`:
  - `int call_add(int a, int b);`
  - `std::string call_concat(const std::string& a, const std::string& b);`
  - `int call_compute_value(int x);`
  - `std::string call_get_message();`
  - `int call_multiply(int a, int b);` (uses `ModuleA::Calculator` instance)
  - `std::string call_calculator_info();` (calls `Calculator::info()`)

- Combined wrappers that use both `ModuleA` and `ModuleB`:
  - `int call_add_both(int a, int b);`
  - `std::string call_concat_both(const std::string& a, const std::string& b);`
  - `int call_compute_value_both(int x);`
  - `std::string call_get_message_both();`
  - `int call_multiply_both(int a, int b);`
  - `std::string call_calculator_info_both();`

- Legacy adapters:
  - Direct legacy calls: `call_legacy_add`, `call_legacy_multiply`, `call_legacy_calculator_info`.
  - Calls that route legacy functionality via `ModuleA` or `ModuleB` adapter APIs.

- Utility and small types:
  - `template<typename T> T call_twice(T v);` — header inline template.
  - `struct NumberInfo { size_t value; };`
  - `NumberInfo GetIntNumberInfo(int v);`
  - `NumberInfo GetStringNumberInfo(const std::string& s);`
  - `std::string call_pair_int_to_string(int a, int b);`
  - `std::string call_pair_string_int_to_string(const std::string& s, int n);`

- Small free functions that use imported template modules:
  - `int addInt(int a, int b);`
  - `double mulDouble(double a, double b);`
  - `int addThenMulInt(int a, int b, int c);`

## Dependencies (within this solution)

- `ModuleA` — main module used by many wrappers.
- `ModuleB` — second module used for combined behavior.
- `Legacy` — legacy code adapters and classes.
- `ModuleT` — provides templated utilities such as `Pair` and number providers.
- `TemplateA` / `TemplateB` — template modules imported for helper functions.
- `ModulesTest` — unit tests reference the `Caller` API.

## Build and Tooling Notes

- Requires a C++20-compliant toolchain (project configured for C++20 modules).
- Uses Visual Studio precompiled header `pch.h` in the translation unit.
- Built as part of the `ModuleExample` solution.
- The project imports several C++20 modules; ensure project/module references are present when opening the solution in Visual Studio.

## C++ features used

- C++20 modules (`import ModuleA;`, `import ModuleB;`, `import Legacy;`, `import ModuleT;`, `import templatea;`, `import templateb;`).
- Header-implemented function templates and inline templates (`call_twice`, `Pair<T,U>` usage).
- Namespaces (nested namespace `moduleexample::caller`).
- Classes and static member functions (`Calculator::info()`, `LegacyCalculator`).
- `std::string` and standard library streams (`std::ostringstream`).
- Plain-old-data structs (`NumberInfo`).
- Inter-module composition (combining results from multiple modules).

## Testing

Unit tests that exercise the `Caller` API reside in the `ModulesTest` project. Run the test project after building the solution.

## Notes

- No external links or third-party dependencies are required by this project.
- This README is intended to be placed at `Caller/README.md` as the project-level documentation.