# 02_RangesAndViewsTest

This test project contains GoogleTest unit tests that validate the utilities in the sibling `02_RangesAndViews` project. The tests materialize and evaluate range/view results and verify expected behavior for common view compositions.

## Contents

- `02_RangesAndViewsTest.cpp` — GoogleTest cases covering:
  - `filterEven` — verifies filtered even elements are produced from input vectors.
  - `squareAll` — validates element-wise squaring via a transform view.
  - `evenSquares` — tests composed filter+transform view producing squares of even numbers.
  - `filterOddLessThanTen` — checks composition of multiple filters and `take` with materialization to `std::vector<int>`.
  - `dropFirstThreeAndToString` — verifies dropping elements, transforming to `std::string`, and aggregation into a single string.
  - `enumerate` — asserts index-element pairing produced by materializing an `iota`-based sequence.
  - `filterAndSquareOptional` — confirms optional-producing transform, filtering of empty optionals, and unwrapping via chained views.
- `TestUtilities/TestUtils.h` — small test utility providing `captureOutput(Func&&)` for capturing stdout when tests need to assert on printed output.

## Test framework

- Tests use GoogleTest. Ensure the test runner links and runs GoogleTest to execute these cases.

## C++ features used in the test project

- Standard library containers and utilities (`std::vector`, `std::string`, `std::accumulate`).
- Iterator-based materialization (constructing containers from view iterators).
- Lambda expressions and initializer lists used within tests.
- GoogleTest macros and assertions (`TEST`, `EXPECT_EQ`, `ASSERT_EQ`).

Note: The code under test uses C++20 Ranges and Concepts; the tests primarily materialize and inspect results and do not require advanced C++20 language features beyond typical library usage.

## Notes

- Tests reference the header-only utilities in `..\\02_RangesAndViews\\02_RangesAndViews.h`.
- No usage examples are included in this README; run the test suite to observe concrete behavior and usage patterns.