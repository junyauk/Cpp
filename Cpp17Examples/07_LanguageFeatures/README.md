# 07_LanguageFeatures

## Overview

This project demonstrates several C++17 language features and attributes that improve safety and expressiveness: `[[nodiscard]]`, `[[maybe_unused]]`, `if constexpr`, inline variables, and `noexcept` specifiers with compile-time traits.

## Features

- `[[nodiscard]]`
  - `ComputeValue(int)` is marked `[[nodiscard]]` to warn when return value is ignored.
  - `struct Result` is marked `[[nodiscard]]` to encourage checking returned aggregate values.

- `[[maybe_unused]]`
  - `UnusedFunction()` and local variables/lambdas in `MaybeUnusedExample()` demonstrate suppressing unused warnings where appropriate.

- `if constexpr`
  - `TypeName<T>()` uses `if constexpr` with type traits to select behavior at compile time for integral, floating-point, or other types.

- Inline variables
  - `inline int GlobalCounter` and `inline static` class members (e.g., `Config::MaxValue`) illustrate shared inline variables across translation units versus `static` variables with internal linkage.
  - Helper functions `incrementA/B/C()` and `getCountersA/B/C()` show differences between `static` and `inline` storage.

- `noexcept` with type traits
  - `MightThrow<T>()` uses `noexcept(std::is_integral_v<T>)` and `if constexpr` to conditionally throw for non-integral types.

## Public API (summary)

- `[[nodiscard]] int ComputeValue(int x)`
- `struct [[nodiscard]] Result { int value; std::string description; }`
- `[[maybe_unused]] inline void UnusedFunction()`
- `void MaybeUnusedExample()`
- `template<typename T> std::string TypeName()`
- `inline int GlobalCounter` and `inline int inlineCounter`
- `inline static int Config::MaxValue` and `Config::sharedValue`
- `static int staticCounter`
- `void incrementA(), incrementB(), incrementC()`
- `std::vector<int> getCountersA(), getCountersB(), getCountersC()`
- `std::string reportValues()`
- `template<typename T> void MightThrow() noexcept(...)`

## Requirements

- Visual Studio with C++17 support (MSVC toolset compatible with C++17).

## Building

Open the solution or the `07_LanguageFeatures` project in Visual Studio and build using the IDE. Select the desired configuration (Debug or Release) and platform, then build the project. The produced binaries will be in the project's output directory (for example, `Debug\` or `Release\` under the project folder).

## Running

The project contains lightweight utility functions. Run the `07_LanguageFeatures` binary if present or use the provided unit tests to exercise the behavior. Functions may not print to console; inspect return values or run tests.

## Tests

A test project `07_LanguageFeaturesTest` is included and covers:

- `ComputeValue` and `Result` usage
- `MaybeUnused` examples
- `TypeName<T>()` behavior for `int`, `double`, and `std::string`
- Inline vs static variable semantics and shared counters across translation units
- `MightThrow<T>()` noexcept behavior

Use Visual Studio's __Test Explorer__ to run the tests or execute the test binary from the test project's output folder.

## Notes

- Prefer `[[nodiscard]]` for functions whose return values must not be ignored.
- Use `[[maybe_unused]]` to document intentionally unused entities and suppress warnings.
- `if constexpr` is evaluated at compile time and enables writing branch code that may only be valid for certain template parameters.
- Inline variables simplify single-definition semantics for globals across translation units (C++17).
- `noexcept` can be templated via type traits to express exception guarantees dependent on template parameters.

## License

See the repository `LICENSE` file for license details.