# 08_ConstexprAdvanced

This project demonstrates advanced compile-time computation techniques using C++20 `constexpr` and `consteval`. The header-only examples provide functions and templates that can be evaluated at compile time and, where applicable, enforced to be evaluated during compilation.

## Contents

- `08_ConstexprAdvanced.h` — Header-only examples including:
  - `factorial(int)` — a `constexpr` recursive factorial function that can be evaluated at compile time.
  - `gcd(unsigned int, unsigned int)` — a `constexpr` implementation of the greatest common divisor using recursion.
  - `sum(const std::array<int, N>&)` (in `ConstExprSamples`) — a `constexpr` template that computes the sum of array elements; uses range-based for (C++20) for clarity.
  - `str_len(const char*)` — a `constexpr` function to compute string length at compile time.
  - `ConstArrayUtils::sum` and `ConstArrayUtils::max` — `consteval` template functions that must be evaluated at compile-time to compute aggregate values and the maximum element of an array.

## C++20 features used

- `constexpr` functions and templates — compile-time evaluable functions (`factorial`, `gcd`, `sum`, `str_len`).
- `consteval` — functions that are required to be evaluated at compile time (`ConstArrayUtils::sum`, `ConstArrayUtils::max`).
- Template parameter deduction and non-type template parameters (`std::array<T, N>` specialization and `template<size_t N>` usage).
- Range-based for loops in `constexpr` context (enabled by C++20) for clearer compile-time iteration.
- `std::array` and `std::string_view` for fixed-size arrays and lightweight string views used in header declarations.

## Requirements

- C++20 compatible compiler and standard library with support for `constexpr` and `consteval` evaluation semantics.

## Testing

- Unit tests are located in the sibling test project `08_ConstexprAdvancedTest`. Tests include `static_assert` checks to validate compile-time evaluation and GoogleTest assertions to validate runtime behavior for functions like `factorial`, `gcd`, `sum`, `str_len`, and the `consteval` utilities.

## Notes

- `consteval` forces compile-time evaluation; use it when a result must be known at compile time.
- `constexpr` functions can still be called at runtime; the examples show both compile-time `static_assert` checks and runtime expectations in unit tests.
- No usage examples are included in this README; refer to the test project for concrete validations and compile-time checks.