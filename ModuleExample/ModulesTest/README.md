# ModulesTest

## Overview

`ModulesTest` contains unit tests that validate the behavior and integration of the `Caller`, `MiniModules`, `Modules`, and `Legacy` projects in this solution. Tests exercise both module-based implementations and the wrapper/adaptor surfaces provided by `Caller`.

## Purpose

- Verify correctness of module implementations and legacy adapters.
- Ensure expected inter-module composition (ModuleA, ModuleB, ModuleT) as used by `Caller`.
- Provide automated regression checks for template instantiations and adapter behavior.

## Test Framework

- Google Test (gtest) is used for all test suites.
- Tests are organized into suites that mirror functional areas: Caller basic APIs, combined modules, legacy adapters, MiniModules features, and template/module utilities.

## What is tested (summary)

- Caller basic API:
  - `call_add`, `call_concat`, `call_compute_value`, `call_get_message`, `call_multiply`, `call_calculator_info`
- Combined module behavior:
  - `call_add_both`, `call_concat_both`, `call_compute_value_both`, `call_get_message_both`, `call_multiply_both`, `call_calculator_info_both`
- Legacy adapters:
  - `call_legacy_add`, `call_legacy_multiply`, `call_legacy_calculator_info`
  - Calls routed via `ModuleA` and `ModuleB` adapters (`call_legacy_add_viaModuleA`, `call_legacy_add_viaModuleB`, `call_calculator_legacy_*_viaModuleA/ModuleB`)
- MiniModules features (exercised via Caller wrappers):
  - Hello message, numeric helpers (`computeSquare`, `computeHypotenuse`), and simple string utilities (`caller_to_upper`, `caller_to_lower`)
- Template/module utilities:
  - `ModuleT` templates: `Box<T>`, `Pair<T,U>`, `NumberBox<T>`, `Create*NumberProvider`
  - Template helper functions imported from template modules (e.g. `addInt`, `mulDouble`, `addThenMulInt`)
- Parameterized tests for compute_value behavior across multiple inputs.

## How to run tests

1. Build the entire `ModuleExample` solution so that all module and library projects are up to date.
2. Run the test binary:
   - Use Visual Studio __Test Explorer__ to run and inspect test results, or
   - Execute the compiled `ModulesTest` test executable from the command line to run the Google Test binary.

Ensure module project references and build order are correct so `ModulesTest` can import and link required modules and `Caller` wrappers.

## Dependencies (within this solution)

- `Caller`, `MiniModules`, `Modules`, and `Legacy` projects — tests depend on the produced symbols from these projects.
- Google Test framework integrated in the test project.

## C++ features exercised by tests

- C++20 modules (`import ModuleT;`, module imports used indirectly via `Caller`).
- Function and class templates and explicit instantiation (`ModuleT::Box`, `Pair`, `NumberBox`).
- Template specialization (`NumberBox<std::string>`).
- std::unique_ptr and runtime polymorphism via interface (`INumberProvider`).
- constexpr constants and inter-module constant composition.
- Standard library usage (`std::string`, streams, <cmath> utilities).
- Google Test macros and parameterized tests.

## Notes

- Tests assume the projects are built with a C++20-capable toolchain and that module imports/resolution are correctly configured in the solution.
- No external network resources or documentation links are required by the test suite.