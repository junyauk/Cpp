# Cpp17Examples

## Overview

This solution collects small, focused example projects that demonstrate C++17 language features and standard-library utilities. Each project is self-contained and intended for learning and unit testing with Visual Studio (MSVC) and Google Test.

## Requirements

- Visual Studio with C++17 support (MSVC toolset compatible with C++17).
- No external libraries are required for the examples; many test projects use Google Test (gtest) which is included in test projects' headers.

## Build (Visual Studio)

1. Open the Visual Studio solution `Cpp17Examples.sln`.
2. Ensure each project is configured to use the C++17 language standard.
3. Select the desired configuration (Debug or Release) and platform, then build the solution.

## Run

- Run individual executables from the project's output directory (for example, `Debug\` or `Release\`) or launch them from Visual Studio.
- Many example projects are lightweight utilities or header-only helpers and are primarily exercised via unit tests.

## Tests

- Use Visual Studio's __Test Explorer__ to discover and run unit tests across projects.
- Test project names generally follow the pattern `<NN>_...Test` and are located next to their corresponding example projects.

## Projects (short summary)

- `01_StructuredBindings` / `01_StructuredBindingsTest` — Demonstrates structured bindings with tuples, pairs, and user-defined types.
- `02_Optional` / `02_OptionalTest` — Examples and tests for `std::optional` usage and idioms.
- `03_IfInit` / `03_IfInitTest` — Demonstrates `if` and `switch` with initializer syntax (if-init/switch-init).
- `04_SwitchInit` / `04_SwitchInitTest` — Examples of `switch` initializers and simple lookup helpers.
- `05_Variant` / `05_VariantTest` — Shows `std::variant`, `std::visit`, and visitor helpers.
- `06_CTAD` / `06_CTADTest` — Class Template Argument Deduction (CTAD) examples and overloaded visitor helpers.
- `07_LanguageFeatures` / `07_LanguageFeaturesTest` — Misc language features: attributes (`[[nodiscard]]`, `[[maybe_unused]]`), `if constexpr`, inline variables, and conditional `noexcept`.
- `08_StringView` / `08_StringViewTest` — `std::string_view` usage and lifetime considerations.
- `09_MapSet` / `09_MapSetTest` — Usage patterns for `std::map`, `std::unordered_map`, `lower_bound`/`upper_bound`/`equal_range`, and bucket/load-factor behavior.
- `10_LambdaImprovements` / `10_LambdaImprovementsTest` — Dispatcher examples, lambda async helpers, and cancellation tokens.

## Contributing

- Follow repository-wide coding standards specified in `.editorconfig` and `CONTRIBUTING.md`.
- Add unit tests for new examples or behavior changes where appropriate.

## Notes

- The examples target modern C++ (C++17). When adding code, prefer C++17 idioms used across the solution.
- Many examples assume a multithreaded runtime for tests — ensure threading is supported on the host.

## License

See the repository `LICENSE` file for license details.