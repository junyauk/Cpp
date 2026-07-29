# 08_Constexpr

## Overview

This project demonstrates enhancements to `constexpr` in C++20 and techniques for writing compile-time-evaluated functions and utilities. Examples emphasize deterministic, constexpr-friendly code patterns and practical use cases where computation can be moved to compile time.

## Requirements

- C++20-capable compiler (Visual Studio 2022 recommended).
- Project configured to use the C++20 language standard.

## Build

1. Open `C++20Features.sln` in Visual Studio 2022.
2. Ensure the C++ Language Standard is set to C++20 (Project Properties → C/C++ → __Language__).
3. Build the `08_Constexpr` project or the entire solution.

Precompiled headers (`pch.*`) are provided for convenience.

## Contents

- `Constexpr_Basic.h` — primary header showcasing `constexpr` functions, `constexpr` variables, and compile-time computation patterns. Examples illustrate how to write functions that can be evaluated at compile time and how to design APIs that are constexpr-friendly.
- `08_Constexpr.vcxproj` — Visual Studio project file.
- `pch.h` / `pch.cpp` — precompiled header support.

## Tests

- `08_ConstexprTest` contains unit tests that validate constexpr behavior, ensuring compile-time correctness and runtime equivalence where applicable. Tests demonstrate both compile-time evaluation and runtime fallback scenarios.

## Contributing

- Keep examples focused and clearly commented to explain compile-time behavior.
- When adding new constexpr utilities, include tests that demonstrate compile-time evaluation where possible.
- Prefer small, deterministic functions and avoid side effects in constexpr code.

## License

No license file is included by default. Add a `LICENSE` file if you intend to publish or share the repository.