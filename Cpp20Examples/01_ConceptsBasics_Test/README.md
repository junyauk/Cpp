# 01_ConceptsBasics_Test

This test project contains GoogleTest unit tests that validate the examples in the sibling `01_ConceptsBasics` project. The tests exercise the concept-constrained functions and overloads implemented in `01_ConceptsBasics.h`.

## Contents

- `01_ConcptsBasicsTest.cpp` — GoogleTest cases covering:
  - `add` for integral and floating-point types
  - `printLength` behavior via captured output
  - `negativeValue` for signed integral and floating-point types
  - `gcd` function constrained to integral types
  - `process` overload selection for integral vs floating-point values
- `TestUtilities/TestUtils.h` — small test utility providing `captureOutput(Func&&)` which captures stdout for assertions.

## Test framework

- GoogleTest is used for all unit tests. Ensure the test runner environment links and runs GoogleTest correctly to execute these tests.

## C++ features used in this test project

- No C++20-specific language features are required in the test source files. The test code uses the following language/library facilities:
  - Function templates (for `captureOutput`)
  - Lambda expressions and captures (used when calling `captureOutput`)
  - Standard library types such as `std::string`
  - GoogleTest macros (`TEST`, `EXPECT_EQ`, `EXPECT_DOUBLE_EQ`)

The codebase being tested uses C++20 Concepts; the tests themselves do not rely on Concepts language features.

## Notes

- The tests reference the header-only examples in `..\\01_ConceptsBasics\\01_ConceptsBasics.h` and validate behavior by calling functions and capturing stdout where appropriate.
- No usage examples are included in this README. Run the test suite to see concrete usage scenarios.