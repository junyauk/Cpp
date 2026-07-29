# 05_VariantTest

## Overview

This test project contains (or is intended to contain) unit tests for the `05_Variant` utilities. Tests should validate behavior of `std::variant` usage, visitor-based conversion via `std::visit`, and mapping for `Color` values.

## Requirements

- Visual Studio with C++17 support (MSVC toolset compatible with C++17).
- Google Test framework integrated into the test project if you choose to use gtest.

## Building

Open the solution or the test project `05_VariantTest` in Visual Studio and build the solution. Ensure the test project compiles successfully.

## Running Tests

- Use Visual Studio's __Test Explorer__ to discover and run tests.
- Alternatively, run the produced test executable from the test project's output directory (for example, `Debug\` or `Release\`) to run all tests from the command line.

## What the tests should cover (suggested)

- `toString` with `IntOrString` holding an `int` and a `std::string`.
- `settingToString` for each alternative in `SettingValue` (`int`, `double`, `std::string`, `Color`).
- Correct string formatting for numeric types and `Color` enum values.
- Edge cases and invalid values where appropriate.

## Notes

- Follow repository-wide coding standards in `.editorconfig` and `CONTRIBUTING.md`.
- Tests should be compiled with C++17.

## License

See the repository `LICENSE` file for license details.