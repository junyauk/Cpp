# 01_ConceptsBasics

This project demonstrates simple C++20 Concepts examples focusing on type constraints, requires-clauses, and function overloading by constrained parameters. The code is intended to be concise reference material for understanding how Concepts can express intent and constrain templates in modern C++.

## Contents

- `01_ConceptsBasics.h` — Header-only examples implementing the following:
  - `Number` concept: constrains a type to integral or floating-point types and an `add` function template specialized for `int` and `double`.
  - `HasLength` concept: detects types that provide a `.length()` convertible to `std::size_t` and a `printLength` helper that prints the length.
  - `SignedValue` concept: matches signed integral types or floating-point types and a `negativeValue` function that negates a value.
  - `gcd` function: an implementation constrained with a `requires std::integral<T>` clause to compute the greatest common divisor for integral types.
  - `process` overloads: two inline overloads constrained with `std::integral` and `std::floating_point` to demonstrate constrained overload resolution.

## C++20 features used

- Concepts (language feature) — `concept` keyword and user-defined concepts such as `Number`, `HasLength`, and `SignedValue`.
- Standard library concepts — `std::integral`, `std::floating_point`, `std::convertible_to`.
- Abbreviated function templates / constrained parameters — use of `HasLength auto`, `std::integral auto`, and `std::floating_point auto` in function parameter lists.
- Requires-clause on templates — `requires std::integral<T>` used on `gcd`.
- Concept expressions and logical operators — combining concepts with `||` and `&&` in concept definitions.
- Constrained template parameter syntax — `template<Number T>` style constrained template parameters.
- Constrained overload resolution — function overloads differentiated by concept constraints.
- Inclusion of the `<concepts>` header to access standard concepts utilities.

These features are observed in `01_ConceptsBasics.h` and demonstrate both user-defined and standard concepts together with the new concise syntax for constraining templates and function parameters.

## Requirements

- C++20 compatible compiler (the code uses `#include <concepts>` and Concepts language features).

## Testing

- Unit tests for this project are located in the sibling test project `01_ConceptsBasics_Test`. The tests use GoogleTest to validate behavior such as `add`, `printLength`, `negativeValue`, `gcd`, and `process` overload selection.

## Notes

- The examples are header-only and intentionally compact for study and demonstration purposes.
- No usage examples are included in this README. Refer to the test project for concrete usage scenarios.