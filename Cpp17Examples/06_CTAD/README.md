# 06_CTAD

## Overview

This project demonstrates C++17 Class Template Argument Deduction (CTAD) and related techniques for writing concise visitor helpers for `std::variant` using CTAD-enabled helper types. The samples include a simple `MyPair` template with a deduction guide, an `Overloaded` helper for `std::visit` that benefits from CTAD, and an example showing move-only types with visitors.

## Features

- `MyPair<T1, T2>` — a simple pair-like template with a deduction guide so you can write `MyPair p(42, std::string("hello"));` without specifying template arguments.
- `Overloaded` helper — a variadic template that inherits from multiple lambda types to create a visitor for `std::visit`. CTAD allows writing `auto visitor = Overloaded{ ... };` without explicit template arguments.
- Move-only example — demonstrates `std::variant` usage with a move-only type (`MoveOnly`) and an `Overloaded` visitor that handles the move-only alternative.

## Public API (summary)

- `CTADExample1::MyPair<T1, T2>`
  - Deduction guide: `MyPair(const T1&, const T2&) -> MyPair<T1, T2>;`
- `CTADExample2::Overloaded` — helper for `std::visit` constructed via CTAD
- `CTADExample3::MoveOnly` — a simple move-capable type used with variant
- `CTADExample3::Overloaded` — visitor helper (CTAD) used with `MoveOnly` and numeric alternatives

## Tests

The solution includes a test project `06_CTADTest` that exercises the examples using Google Test. Tests present:

- `MyPairTest` — verifies template argument deduction and member values.
- `OverloadedTest` — checks visitor behavior for different `std::variant` alternatives.
- `MoveOnlyOverloadedTest` — ensures move-only variant alternatives are handled correctly.
- `VariantHelperTest` and `AnyTest` — additional checks for `std::variant` helpers and `std::any` behavior.

Use Visual Studio's Test Explorer to run the tests or run the test binary from the project's output directory.

## Requirements

- Visual Studio with C++17 support (MSVC toolset compatible with C++17).

## Building

Open the solution or the `06_CTAD` project in Visual Studio and build using the IDE. Select the desired configuration (Debug or Release) and platform, then build the project. The produced binaries will be in the project's output directory (e.g. `Debug\` or `Release\`).

## Running

The sample `example()` functions in the headers print to `std::cout` for quick demonstration. They are primarily intended for unit tests and small demos.

## Notes

- CTAD can reduce verbosity when constructing class templates, especially for small utility types.
- The `Overloaded` helper paired with `std::variant` and `std::visit` is a common idiom to write concise visitors in modern C++.
- Follow repository-wide coding standards in `.editorconfig` and `CONTRIBUTING.md`.

## License

See the repository `LICENSE` file for license details.