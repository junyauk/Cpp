# 02_Optional

## Overview

This project demonstrates use of `std::optional` (C++17) through a set of utility functions and small types. It illustrates typical patterns: returning optional values, checking for value presence, using `value_or`, `emplace`, `reset`, and integrating `std::optional` with control-flow (if-init) and parsing.

## Features

- Functions that return `std::optional` to indicate presence/absence of a value:
  - `toStringIfPositive(int)` — returns string form when input > 0.
  - `getLengthIfHasValue(const std::optional<std::string>&)` — returns optional length if string present.
  - `makeOptionalInt(int)` — creates an optional integer.
  - `findInVector(const std::vector<int>&, int)` — searches a vector and returns optional index.
  - `parseInt(const std::string&)` — parses an integer using `std::from_chars`, returns `std::optional<int>`.
- Utility functions demonstrating optional manipulation:
  - `getValueOrDefault(const std::optional<std::string>&, const std::string&)` — uses `value_or`.
  - `reEmplaceValue(std::optional<std::string>&, const std::string&)` — uses `emplace` to replace stored value.
  - `resetOptional(std::optional<std::string>&)` — clears the optional.
- Small types showing optional members and three-state logic:
  - `struct Config { std::optional<int> port; }`
  - `struct Settings { std::optional<bool> enableLogging; }`

## Public API (summary)

- `std::optional<std::string> toStringIfPositive(int value)`
- `std::optional<size_t> getLengthIfHasValue(const std::optional<std::string>& strOpt)`
- `std::string getValueOrDefault(const std::optional<std::string>& strOpt, const std::string& defaultValue)`
- `std::optional<int> makeOptionalInt(int value)`
- `void reEmplaceValue(std::optional<std::string>& opt, const std::string& newValue)`
- `void resetOptional(std::optional<std::string>& opt)`
- `std::optional<size_t> findInVector(const std::vector<int>& vec, int target)`
- `std::optional<int> parseInt(const std::string& text)`
- `struct Config { std::optional<int> port; }`
- `struct Settings { std::optional<bool> enableLogging; }`

## Requirements

- Visual Studio with C++17 support (MSVC toolset compatible with C++17).
- No external libraries required.

## Building

Open the solution or the `02_Optional` project in Visual Studio and build using the IDE. Select the desired configuration (Debug or Release) and platform, then build the project. The produced executable will be located in the project's output directory (for example, `Debug\` or `Release\` under the project folder).

## Running

Run the produced executable from the project's output directory or launch it from Visual Studio. The utilities print minimal or no output; check returned optionals programmatically or run the accompanying tests.

## Tests

There is a test project `02_OptionalTest` that uses the repository's test framework. Tests exercise:

- Presence/absence semantics for returned optionals.
- `value_or`, `emplace`, `reset`, and operator-> usage.
- Search helpers and parse behavior using `std::from_chars`.
- Optional-based control flow (if-init) and three-state boolean logic.

Use Visual Studio's Test Explorer to run the tests or execute the test binary from the output directory.

## Notes

- Follow repository-wide coding standards in `.editorconfig` and `CONTRIBUTING.md`.
- `parseInt` uses `std::from_chars` which avoids exceptions and locale issues.

## License

See the repository `LICENSE` file for license details.