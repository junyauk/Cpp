# 04_StdSpanTest

This test project contains GoogleTest unit tests that validate the `std::span`-based utilities in the sibling `04_StdSpan` project. The tests exercise span interoperability with arrays, `std::array`, and `std::vector`, as well as behavior for slicing, fixed-size extents, and in-place modification.

## Contents

- `04_StdSpanTest.cpp` — GoogleTest cases covering:
  - `Sum` with C-style arrays and `std::vector`.
  - `GetSubspan` and subspan slicing from `std::array`.
  - `ContainsChar` asserting character membership via a `std::string`.
  - `SumMatrix` using a flattened matrix represented as a span.
  - `PrintNumbers` and `PrintSlice` validating stdout output for full and partial spans.
  - `FillBuffer` asserting in-place modification through a mutable span.
  - `PrintMatrix` validating a fixed-size span (`std::span<int, 9>`) used to print a 3x3 matrix.
- `TestUtilities/TestUtils.h` (project-wide) — small helper used elsewhere for capturing stdout; tests here use `testing::internal::CaptureStdout()` directly.

## Test framework

- GoogleTest is used for all unit tests. Ensure the test runner links and runs GoogleTest to execute these cases.

## C++ features used in the test project

- `std::span` (`<span>`) — construction from arrays, `std::vector`, and `std::array`, including fixed-size extents (`std::span<T, N>`).
- Span slicing and subspans (`subspan`) to create views over portions of data.
- Interoperability with legacy arrays and container types without copying.
- Use of standard algorithms/utilities via span iterators (e.g., `std::accumulate` used by the code under test).
- GoogleTest macros and assertions (`TEST`, `EXPECT_EQ`, `EXPECT_TRUE`) and test helpers for capturing stdout.

## Notes

- Tests reference `..\\04_StdSpan\\04_StdSpan.h` and validate both value-returning and output-producing functions.
- No usage examples are included in this README; run the test suite to observe concrete behavior and expected outputs.