# 05_Variant

## Overview

This project demonstrates the use of `std::variant` and `std::visit` (C++17) for type-safe, value-discriminated unions. The samples show how to model values that can be one of several types and how to implement visitor-based conversion to `std::string`.

## Features

- `using IntOrString = std::variant<int, std::string>` — a simple variant that holds either an `int` or a `std::string`.
- `std::string toString(const IntOrString&)` — converts a variant value to a string using `std::visit` and `if constexpr` type checks.
- `enum class Color { Red, Green, Blue }` and `using SettingValue = std::variant<int, double, std::string, Color>` — a richer variant used for configuration-like settings.
- `std::string settingToString(const SettingValue&)` — visits `SettingValue` and returns a decorated string representation (`int:...`, `double:...`, `string:...`, `Color:...`).

## Public API (summary)

- `using IntOrString = std::variant<int, std::string>`
- `std::string toString(const IntOrString& v)`
- `enum class Color { Red, Green, Blue }`
- `using SettingValue = std::variant<int, double, std::string, Color>`
- `std::string settingToString(const SettingValue& v)`

## Requirements

- Visual Studio with C++17 support (MSVC toolset compatible with C++17).

## Building

Open the solution or the `05_Variant` project in Visual Studio and build using the IDE. Select the desired configuration (Debug or Release) and platform, then build the project. The produced executable will be located in the project's output directory (for example, `Debug\` or `Release\` under the project folder).

## Running

Run the produced executable from the project's output directory or launch it from Visual Studio. The sample functions are utility-like and return strings; they are primarily intended for unit tests and demonstration.

## Tests

Check for an existing test project that covers variant usage (e.g. confirming `toString` and `settingToString` behavior). If no test project exists, consider adding tests verifying:

- `toString` for both `int` and `std::string` cases.
- `settingToString` for each alternative in `SettingValue`, including `Color` values.

Use Visual Studio's Test Explorer to run tests or execute the test binary from the output directory.

## Notes

- `std::variant` together with `std::visit` and `if constexpr` provides a powerful, zero-overhead alternative to inheritance-based polymorphism for small discriminated unions.
- Follow repository-wide coding standards in `.editorconfig` and `CONTRIBUTING.md`.
- This code targets C++17.

## License

See the repository `LICENSE` file for license details.