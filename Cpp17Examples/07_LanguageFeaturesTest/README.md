# 07_LanguageFeaturesTest

## Overview

This test project contains unit tests for the `07_LanguageFeatures` samples. Tests use Google Test to validate behavior of various C++17 language features and attributes demonstrated in the sample headers.

## Requirements

- Visual Studio with C++17 support (MSVC toolset compatible with C++17).
- Google Test framework integrated into the test project.

## Building

Open the solution or the `07_LanguageFeaturesTest` project in Visual Studio and build the solution. Ensure the test project compiles successfully.

## Running Tests

- Use Visual Studio's __Test Explorer__ to discover and run the tests.
- Alternatively, run the produced test executable from the test project's output directory (for example, `Debug\` or `Release\`) to run tests from the command line.

## Tests included

- `NodiscardFunction` — verifies `[[nodiscard]]` usage for function and struct return values.
- `MaybeUnused` — exercises `[[maybe_unused]]` usage for functions, local variables, and lambdas.
- `IfConstexpr` — validates `TypeName<T>()` behavior using `if constexpr` for `int`, `double`, and `std::string`.
- `InlineVariable` and `StaticVsInline` — checks inline vs static variable semantics across translation units, shared inline variables, and `Config::MaxValue`.
- `NoexceptTrait` — confirms conditional `noexcept` behavior for `MightThrow<T>()`.
- Counters and `reportValues()` — ensures expected values for static/inline/shared counters after increments.

## Notes

- Tests rely on C++17 features; set project language standard accordingly.
- Follow repository-wide coding standards in `.editorconfig` and `CONTRIBUTING.md`.

## License

See the repository `LICENSE` file for license details.