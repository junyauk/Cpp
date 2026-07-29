# 03_StdFormat

This project demonstrates C++20 text formatting using the standard formatting library (`<format>`). The examples provide concise, header/source-based functions that show how to format strings, numbers, and date/time values with format specifiers, alignment, padding, and locale-independent output.

## Contents

- `03_StdFormat.h` / `03_StdFormat.cpp` — Implementations include:
  - `formatGreeting` — simple positional replacement into a greeting string.
  - `formatScore` — formatting mixed string and integer values.
  - `formatPI` — formatting floating-point values with adjustable precision using dynamic precision specifiers.
  - `formatDateTime`, `formatDateYMD`, `formatDateDMY`, `formatTimeHMS`, `formatDateTimeISO`, `formatDateWithWeekday`, `formatDateTimeLong` — various date/time formatting functions that accept `std::chrono::sys_seconds` or `std::chrono::sys_days` and format them using chrono format specifiers.
  - `formatExam01`..`formatExam04` — examples demonstrating alignment, fill characters, width, alternate form prefixes, numeric base formatting, and other format specifiers.

## C++20 features used

- `std::format` (Formatting library, `<format>`) — type-safe formatting with Python/printf-like format specifiers.
- Chrono formatting integration — formatting `std::chrono::sys_seconds` and `std::chrono::sys_days` with `std::format` using `%`-style chrono specifiers.
- Dynamic precision in format strings — using `{:.{}f}` to supply precision at runtime.
- Format specifiers for alignment, fill, width, and alternate forms — examples use `^`, `>`, fill characters, `#` for alternate form, and format type specifiers such as `X`, `b`, and `f`.
- `std::numbers` for mathematical constants (`std::numbers::pi`).

## Requirements

- C++20 compatible compiler and standard library with `<format>` support and chrono formatting support.

## Testing

- Unit tests for this project are located in the sibling test project `03_StdFormatTest`. The tests use GoogleTest to validate the formatted strings, including date/time patterns and exact expected outputs for example format cases.

## Notes

- The functions demonstrate idiomatic usage of `std::format` for common formatting scenarios and for producing locale-independent textual representations.
- No usage examples are included in this README; refer to the test project for concrete behavior validations.