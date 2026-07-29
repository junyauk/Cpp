# 04_SwitchInit

## Overview

This project demonstrates C++17 "switch" statements with initializer declarations (switch-init) and related conditional patterns. The samples illustrate how initializer syntax can make switch-based classification and lookup code more concise and expressive.

## Features

- `classifyByModulo(int)` — demonstrates `switch (auto v = value % 3; v)` to branch on the remainder of a modulo operation.
- `isVowel(char)` — shows switching on a character code using an initializer and handling multiple cases in a compact form.
- `enum class Color` — a small enumeration used by color conversion helpers.
- `toColor(const std::string&)` — maps string names to `Color` values using a lookup table and `if (auto it = table.find(name); it != table.end())`.
- `toColorOrUnknown(const std::optional<std::string>&)` — demonstrates combining optional values with switch-init to map an optional string to a `Color`, returning `Color::Unknown` when appropriate.

## Public API (summary)

- `std::string classifyByModulo(int value)` — returns a descriptive string based on `value % 3`.
- `bool isVowel(char ch)` — returns true if `ch` is an ASCII vowel.
- `enum class Color { Red, Green, Blue, Unknown }`
- `Color toColor(const std::string& name)` — returns a `Color` for known names; `Color::Unknown` otherwise.
- `Color toColorOrUnknown(const std::optional<std::string>& name)` — maps an optional string to a `Color` or returns `Color::Unknown`.

## Requirements

- Visual Studio with C++17 support (MSVC toolset compatible with C++17).

## Building

Open the solution or the `04_SwitchInit` project in Visual Studio and build using the IDE. Select the desired configuration (Debug or Release) and platform, then build the project. The produced executable will be located in the project's output directory (for example, `Debug\` or `Release\` under the project folder).

## Running

Run the produced executable from the project's output directory or launch it from Visual Studio. The functions are utility-like and primarily intended for demonstration and unit tests.

## Tests

No test project is included specifically for `04_SwitchInit` in this solution. You may add unit tests covering classification results and color mapping behavior.

## Notes

- `switch` initializers are particularly useful when you need to compute a temporary value before branching and keep its scope limited to the switch statement.
- Follow repository-wide coding standards in `.editorconfig` and `CONTRIBUTING.md`.
- This code targets C++17.

## License

See the repository `LICENSE` file for license details.