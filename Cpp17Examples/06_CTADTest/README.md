# 06_CTADTest

## Overview

This test project contains unit tests for the `06_CTAD` examples. Tests are implemented using Google Test and validate Class Template Argument Deduction (CTAD) examples, overloaded visitor helpers for `std::visit`, and variant/any behavior.

## Requirements

- Visual Studio with C++17 support (MSVC toolset compatible with C++17).
- Google Test integrated into the test project (the repository includes `gtest` usage).

## Building

Open the solution or the `06_CTADTest` project in Visual Studio and build the solution. Ensure the test project compiles successfully.

## Running Tests

- Use Visual Studio's __Test Explorer__ to discover and run the tests.
- Alternatively, run the produced test executable from the test project's output directory (for example, `Debug\` or `Release\`) to run all tests from the command line.

## Tests included

- `MyPairTest` — verifies that `MyPair` deduction guides correctly deduce template arguments and that members hold expected values.
- `OverloadedTest` — checks `Overloaded` visitor behavior when visiting `std::variant` alternatives (`int`, `std::string`, `bool`).
- `MoveOnlyOverloadedTest` — validates `std::variant` usage with a move-only type (`MoveOnly`) and confirms visitors handle move-only alternatives.
- `VariantHelperTest` — verifies helpers such as `std::holds_alternative` for different variant states.
- `AnyTest` — checks `std::any` type information and casting behavior, including throwing on bad cast and storing custom move-only types.

## Notes

- Tests rely on C++17 features (CTAD, `std::variant`, `std::any`, etc.). Make sure the project is configured for C++17.
- Follow repository-wide coding standards in `.editorconfig` and `CONTRIBUTING.md`.

## License

See the repository `LICENSE` file for license details.