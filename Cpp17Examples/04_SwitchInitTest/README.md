# 04_SwitchInitTest

## Overview

This test project is intended to contain unit tests for the `04_SwitchInit` samples (demonstrating C++17 switch-init and related patterns). If a test project is present in the solution, it should use Google Test or another unit test framework to validate classification and mapping behaviors.

## Requirements

- Visual Studio with C++17 support (MSVC toolset compatible with C++17).
- Google Test framework if you choose to implement tests using gtest.

## Suggested Tests

- `classifyByModulo` — verify descriptive results for various integer inputs (e.g. values producing remainder 0, 1, 2).
- `isVowel` — test ASCII vowel and non-vowel characters (both uppercase and lowercase).
- `toColor` — validate mapping from known names to `Color` enum values and fallback to `Color::Unknown` for unknown names.
- `toColorOrUnknown` — test behavior with `std::optional<std::string>` present and absent.

## Building

Open the solution or the test project in Visual Studio and build the solution. Ensure the test project compiles successfully.

## Running Tests

- Use Visual Studio's __Test Explorer__ to discover and run the tests.
- Alternatively, run the produced test executable from the test project's output directory (for example, `Debug\` or `Release\`) to run all tests from the command line.

## Notes

- Follow repository-wide coding standards in `.editorconfig` and `CONTRIBUTING.md`.
- Tests should be compiled with C++17.

## License

See the repository `LICENSE` file for license details.