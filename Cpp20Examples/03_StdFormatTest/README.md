# 03_StdFormatTest

This test project contains GoogleTest unit tests that validate the formatting utilities in the sibling `03_StdFormat` project. The tests verify string formatting, numeric formatting with dynamic precision, and chrono-based date/time formatting.

## Contents

- `03_StdFormatTest.cpp` — GoogleTest cases covering:
  - `formatGreeting` and `formatScore` — simple string and integer formatting checks.
  - `formatPI` — verifies floating-point formatting with runtime precision.
  - `formatDateTime`, `formatDateYMD`, `formatDateDMY`, `formatTimeHMS`, `formatDateTimeISO`, `formatDateWithWeekday`, `formatDateTimeLong` — validates date/time formatting for `std::chrono::sys_seconds` / `std::chrono::sys_days`.
  - Example format cases (`formatExam01`..`formatExam04`) — asserts alignment, fill, width, alternate forms, and numeric base formatting expected outputs.

## Test framework

- GoogleTest is used for all unit tests. Ensure the test runner links and runs GoogleTest to execute these tests.

## C++ features used in this test project

- Chrono utilities and types (`std::chrono::sys_days`, `std::chrono::sys_seconds`, and `std::chrono::floor`) for constructing and normalizing time points used in assertions.
- Regular expressions (`std::regex`) to validate formatted date/time patterns.
- GoogleTest macros and assertions (`TEST`, `EXPECT_EQ`, `EXPECT_TRUE`).
- Standard library string handling (`std::string`).

Note: The code under test uses C++20 `std::format` and chrono-format integration; the tests primarily assert formatted outputs and patterns and therefore rely on chrono utilities and regex rather than advanced language features.

## Notes

- Tests reference `..\\03_StdFormat\\03_StdFormat.h` / `.cpp` and verify exact outputs for deterministic cases and pattern matches for current-time formatting.
- No usage examples are included in this README; run the test suite to observe concrete behavior and usage patterns.