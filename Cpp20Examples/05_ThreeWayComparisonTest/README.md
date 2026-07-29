# 05_ThreeWayComparisonTest

This test project contains GoogleTest unit tests that validate the three-way comparison examples in the sibling `05_ThreeWayComparison` project. The tests exercise defaulted and custom `operator<=>`, ordering categories, and comparison behavior for integers and floating-point values including unordered results (NaN).

## Contents

- `05_ThreeWayComparisonTest.cpp` — GoogleTest cases covering:
  - `Person` comparisons using a defaulted `operator<=>` (total ordering and equality checks).
  - `Point` comparisons using a manual `operator<=>` that compares `x` then `y`.
  - `CompareAges` — mapping `std::strong_ordering` results to integer semantics (-1, 0, 1).
  - `CompareInts` — verifying integer three-way comparison formatting into human-readable strings.
  - `CompareDoubles` — verifying floating-point comparisons using `std::partial_ordering`, including handling of NaN (unordered) results.

## Test framework

- GoogleTest is used for all unit tests. Ensure the test runner links and runs GoogleTest to execute these cases.

## C++ features used in the test project

- Three-way comparison semantics via `operator<=>` and `<compare>` types (`std::strong_ordering`, `std::partial_ordering`).
- Defaulted comparison operators (`= default`) for concise total ordering and automatic equality.
- Use of `std::numeric_limits<double>::quiet_NaN()` in tests to exercise unordered floating-point comparisons.
- GoogleTest macros and assertions (`TEST`, `EXPECT_TRUE`, `EXPECT_EQ`).

## Requirements

- C++20 compatible compiler and standard library with support for three-way comparison (`operator<=>`) and `<compare>`.

## Notes

- The tests assert both relational operator behavior and formatted comparison results. Special floating-point values (NaN) produce unordered comparisons, which the implementation under test represents by producing an empty string in the corresponding test case.
- No usage examples are included in this README; run the test suite to observe concrete behavior and expected outcomes.