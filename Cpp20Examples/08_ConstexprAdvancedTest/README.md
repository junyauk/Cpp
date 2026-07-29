# 08_ConstexprAdvancedTest

This test project contains GoogleTest unit tests that validate the compile-time and runtime behavior of the utilities in the sibling `08_ConstexprAdvanced` project. Tests verify that functions and templates evaluate correctly at compile time (`static_assert` / `consteval` semantics) and produce the expected runtime results.

## Contents

- `08_ConstexprAdvancedTest.cpp` and `ConstArrayUtilsTest.cpp` — GoogleTest cases covering:
  - Compile-time checks (`static_assert`) and runtime assertions for `factorial`.
  - `gcd` compile-time and runtime validation.
  - `ConstExprSamples::sum` — `constexpr` summation over `std::array` with both static and runtime checks.
  - `str_len` — `constexpr` string-length evaluation validated via `static_assert` and runtime checks.
  - `ConstArrayUtils::sum` and `ConstArrayUtils::max` — `consteval` functions that are validated at compile time and asserted at runtime through tests using `constexpr` arrays.

## Test framework

- GoogleTest is used for unit tests. Ensure the test runner is linked with GoogleTest to execute the suite.

## C++ features used in the test project

- `constexpr` functions and variables — compile-time evaluable checks in tests (e.g., `factorial`, `gcd`, `sum`, `str_len`).
- `consteval` semantics exercised indirectly via functions in `ConstArrayUtils` that must be evaluated at compile time.
- `static_assert` for compile-time verification within tests/source.
- `std::array` for fixed-size compile-time arrays used in tests.
- Range-based for loops in `constexpr` contexts (enabled by C++20).
- Standard testing utilities and macros (`TEST`, `EXPECT_EQ`, `static_assert`) from GoogleTest.

## Requirements

- C++20 compatible compiler and standard library with support for `constexpr` and `consteval`.
- GoogleTest linked into the test runner.

## Notes

- Tests combine compile-time (`static_assert` / `consteval`) and runtime assertions to ensure both compile-time evaluability and correct runtime behavior.
- No usage examples are included in this README; run the test suite to observe concrete validations and compile-time checks.