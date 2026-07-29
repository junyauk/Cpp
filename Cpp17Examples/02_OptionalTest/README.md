# 02_OptionalTest

## Overview

This test project contains unit tests for the `02_Optional` utilities. Tests validate behavior of functions that return or manipulate `std::optional`.

## Requirements

- Visual Studio with C++17 support (MSVC toolset compatible with C++17).
- Google Test framework integrated into the test project (the project includes test source files using the `TEST` macro).

## Building

Open the solution or the test project `02_OptionalTest` in Visual Studio and build the solution. Ensure the test project compiles successfully.

## Running Tests

- Use Visual Studio's __Test Explorer__ to discover and run the tests.
- Alternatively, run the produced test executable from the test project's output directory (for example, `Debug\` or `Release\`) to run all tests from the command line.

## What the tests cover

- `toStringIfPositive` returns a value for positive inputs and `std::nullopt` for non-positive inputs.
- `getLengthIfHasValue` returns the length when an optional string is present, and `std::nullopt` otherwise.
- `getValueOrDefault` returns stored value or default via `value_or`.
- `makeOptionalInt`, `reEmplaceValue`, and `resetOptional` behaviors.
- `findInVector` search behavior for found and not found cases.
- `parseInt` parsing success and failure using `std::from_chars`.
- Optional-driven control flow (if-init) and optional-based three-state boolean logic for `Settings`.

## Notes

- Follow repository-wide coding standards in `.editorconfig` and `CONTRIBUTING.md`.
- Tests are written against C++17 features; ensure the project is configured accordingly.

## License

See the repository `LICENSE` file for license details.