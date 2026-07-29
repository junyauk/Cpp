# TestUtilities

This small project provides lightweight test helpers used across the example test suites. The utilities are header-only and intended to make assertions on stdout output and similar test-time interactions simpler.

## Contents

- `TestUtils.h` — A minimal header providing:
  - `captureOutput(Func&& func)` — template helper that captures stdout around a callable by using GoogleTest's internal capture APIs (`testing::internal::CaptureStdout()` / `GetCapturedStdout()`), returning the captured output as `std::string`.

## C++ features used

- Function templates and forwarding (`template<typename Func>` / `Func&&`).
- Lambda expressions are commonly used when calling `captureOutput`.
- No C++20-specific language features are required by the utility itself.

## Requirements

- GoogleTest (the helper relies on `testing::internal::CaptureStdout()` APIs).
- Standard C++ toolchain; the code is compatible with modern C++ standards (no C++20 language features required by the header).

## Usage notes

- The helper is header-only; include `TestUtilities/TestUtils.h` from tests to use `captureOutput`.
- The implementation uses GoogleTest internal capture functions — ensure the test environment links and runs GoogleTest to avoid undefined behavior.
- This README intentionally omits usage examples; refer to the test projects in the repository for concrete calls and assertions.