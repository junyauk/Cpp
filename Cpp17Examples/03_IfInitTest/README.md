# 03_IfInitTest

## Overview

This test project is intended to contain unit tests for the `03_IfInit` samples (demonstrating C++17 if-init and switch-init). Currently the solution does not include a dedicated test project for `03_IfInit`.

## Suggested Tests

If you add a test project, consider covering the following behaviors:

- `findValue` — lookup success and failure, returning `std::optional<std::string>`.
- `classifyString` — classify strings of varying lengths including edge cases (0, 1, 2, >2).
- `findEven` — find first even number and behavior when none exist.
- `checkPassword` — validate length and simple rule checks for weak passwords.

## Requirements

- Visual Studio with C++17 support (MSVC toolset compatible with C++17).
- Google Test framework if you choose to implement tests using gtest.

## Adding Tests (recommended)

1. Create a new test project in the solution (e.g. using the Google Test Project template).
2. Add a project dependency on the `03_IfInit` project or include its headers.
3. Implement tests using `TEST` macros and assertions (`EXPECT_*`, `ASSERT_*`).
4. Build the solution.

## Building and Running Tests

- Use Visual Studio's __Test Explorer__ to discover and run tests.
- Alternatively, run the produced test executable from the test project's output directory (for example, `Debug\` or `Release\`) to run tests from the command line.

## Notes

- Follow repository-wide coding standards in `.editorconfig` and `CONTRIBUTING.md`.
- Tests should be compiled with C++17.

## License

See the repository `LICENSE` file for license details.