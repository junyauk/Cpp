# Modules Project

## Overview

The `Modules` project groups several C++20 modules used by the `ModuleExample` solution. These modules provide core functionality (numeric and string utilities), adapters for legacy code, and reusable template utilities. The primary modules are `ModuleA`, `ModuleB`, and `ModuleT`; additional small template modules (`TemplateA`, `TemplateB`) are used for simple template helpers.

## Purpose

- Demonstrate organization of functionality into C++20 modules.
- Provide examples of module-level constants, functions, classes, and template exports.
- Show how modules can depend on a legacy header/module (`Legacy`) and how they can adapt or augment legacy behavior.

## Public API (summary)

- ModuleA (namespace: `moduleexample::modulea`)
  - Constants:
    - `constexpr int kModuleAValue = 100`
    - `constexpr int kModuleACombinedValue = kModuleAValue + kLegacyValue`
  - Functions:
    - `int add(int a, int b);` — adapted addition ((a + b) * 10 in tests)
    - `std::string concat(const std::string& a, const std::string& b);` — returns formatted concatenation (`[A|B]`)
    - `int compute_value(int x);` — sample computation ((x + 1) * 100)
    - `std::string message();` — module message (`"ModuleA says hi!"`)
  - Classes:
    - `class Calculator` with instance method `multiply(int, int)` and static `info()`.
    - Adapter members that call into `Legacy` (`legacy_multiply`, `legacy_info`).
  - Adapter functions:
    - `int legacy_add_viaModuleA(int a, int b);`

- ModuleB (namespace: `moduleexample::moduleb`)
  - Constants:
    - `constexpr int kModuleBValue = 200`
    - `constexpr int kModuleBCombinedValue = kModuleBValue + kLegacyValue + 1`
  - Functions:
    - `int add(int a, int b);` — (a + b) * 100 in tests
    - `std::string concat(const std::string& a, const std::string& b);` — returns formatted string (`<A,B>`)
    - `int compute_value(int x);` — ((x + 1) * 1000)
    - `std::string message();` — (`"ModuleB says hello!"`)
  - Classes:
    - `class Calculator` with `multiply`, `info`, and legacy adapter methods.
  - Adapter functions:
    - `int legacy_add_viaModuleB(int a, int b);`

- ModuleT (namespace: `moduleexample::modulet`)
  - Templates and utilities exported for reuse:
    - `template<typename T> T twice(T v);`
    - `template<typename T> class Box` — simple value holder (explicit instantiations exist for `int` and `std::string`).
    - `template<typename T, typename U> class Pair` — with `to_string()` helper (explicit instantiations for common pairs).
    - `template<typename T> class NumberBox` and specialization for `std::string` (returns string length).
    - `class INumberProvider` — abstract interface and `NumberBoxAdapter<T>` adapter.
    - Factory functions:
      - `std::unique_ptr<INumberProvider> CreateIntNumberProvider(int value);`
      - `std::unique_ptr<INumberProvider> CreateStringNumberProvider(const std::string& value);`

- Template helper modules (`TemplateA`, `TemplateB`)
  - Provide small template functions used by `Caller` (e.g. `add`, `mul`, `add_then_mul`) and are imported by consumers.

## Dependencies (within this solution)

- `Legacy` — modules import or use legacy APIs and constants to demonstrate adaptation.
- `Caller` — consumes all modules and provides a unified wrapper API used by tests.
- `ModulesTest` — contains unit tests that validate the composed behavior.

## Build and Tooling Notes

- Requires a C++20-capable compiler and a project configuration that supports C++20 modules (Visual Studio projects in this solution are configured accordingly).
- Module interfaces are implemented as `.ixx` interface units with accompanying implementation files where templates and explicit instantiations may reside.
- When opening the solution in Visual Studio, ensure module project references and import paths are intact so that modules can be imported by dependents.

## C++ features used

- C++20 modules (exported modules and imports).
- Exported constants (`constexpr`) and functions.
- Classes with instance and static members.
- Template classes and functions (class templates, function templates, explicit instantiation of templates).
- Specialization of class templates (e.g. `NumberBox<std::string>`).
- std::unique_ptr and runtime polymorphism via abstract interfaces (`INumberProvider`).
- Inter-module adaptation of legacy APIs and constants.

## Testing

- Unit tests live in the `ModulesTest` project and exercise module behavior through `Caller` wrappers. Build the solution and run the test suite to validate behavior.

## Notes

- This README focuses on module responsibilities and how they are composed in the solution.
- No external links or third-party dependencies are required.