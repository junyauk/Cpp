# 08_StringViewTest

## Overview

This test project contains unit tests for the `08_StringView` samples. Tests validate correct usage patterns and lifetime considerations of `std::string_view`.

## Requirements

- Visual Studio with C++17 support (MSVC toolset compatible with C++17).
- Google Test framework integrated into the test project.

## Building

Open the solution or the `08_StringViewTest` project in Visual Studio and build the solution. Ensure the test project compiles successfully.

## Running Tests

- Use Visual Studio's __Test Explorer__ to discover and run the tests.
- Alternatively, run the produced test executable from the test project's output directory (for example, `Debug\` or `Release\`) to run all tests from the command line.

## What the tests cover

- Creating `std::string_view` from `std::string` and string literals.
- Ensuring `std::string_view` does not outlive the referenced data.
- `remove_prefix`, `remove_suffix`, and `substr` behaviors.
- Converting `std::string_view` to `std::string` for persistent storage.
- Edge cases: empty views and operations at string boundaries.

## Notes

- `std::string_view` is a non-owning view; tests emphasize ownership and lifetime safety.
- Follow repository-wide coding standards in `.editorconfig` and `CONTRIBUTING.md`.

## License

See the repository `LICENSE` file for license details.