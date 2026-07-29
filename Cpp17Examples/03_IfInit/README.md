# 03_IfInit

## Overview

This project demonstrates C++17 "if" and "switch" statements with initializer declarations (if-init and switch-init). The sample utilities show how initializer syntax can simplify common conditional and loop patterns.

## Features

- `findValue(const std::map<int, std::string>&, int)` — demonstrates `if (auto it = m.find(key); it != m.end())` for safe lookup and returning `std::optional<std::string>`.
- `classifyString(const std::string&)` — shows `switch (auto len = input.size(); len)` using initializer in `switch` to branch on string length.
- `findEven(const std::vector<int>&)` — uses `if (auto n = numbers[i]; n % 2 == 0)` inside a loop to find the first even number, returning `std::optional<int>`.
- `checkPassword(const std::string&)` — uses `if`/`else if` with an initializer for concise length checks and simple rule evaluation.

## Public API (summary)

- `std::optional<std::string> findValue(const std::map<int, std::string>& m, int key)`
- `std::string classifyString(const std::string& input)`
- `std::optional<int> findEven(const std::vector<int>& numbers)`
- `std::string checkPassword(const std::string& pwd)`

## Requirements

- Visual Studio with C++17 support (MSVC toolset compatible with C++17).

## Building

Open the solution or the `03_IfInit` project in Visual Studio and build using the IDE. Select the desired configuration (Debug or Release) and platform, then build the project. The produced executable will be located in the project's output directory (for example, `Debug\` or `Release\` under the project folder).

## Running

Run the produced executable from the project's output directory or launch it from Visual Studio. The functions are utility-like and mainly intended for unit tests or demonstration; they produce minimal console output.

## Tests

No unit-test project is included for `03_IfInit` in this solution. Add a test project using Google Test or another framework if required.

## Notes

- These samples focus on clarity: prefer initializer forms when a temporary variable is needed only for a single conditional check.
- Follow repository-wide coding standards in `.editorconfig` and `CONTRIBUTING.md`.
- This code targets modern C++ and uses language features introduced in C++17.

## License

See the repository `LICENSE` file for license details.