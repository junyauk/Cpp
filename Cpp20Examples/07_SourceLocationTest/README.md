# 07_SourceLocationTest

This test project contains GoogleTest unit tests that validate the `std::source_location`-based logging utilities and multi-threaded logging behavior implemented in the sibling `07_SourceLocation` project. Tests assert that messages include call-site metadata and that concurrent logging produces complete entries.

## Contents

- `07_SourceLocationTest.cpp` — GoogleTest cases covering:
  - `logMessage` output includes the provided message, the calling function name, and the calling file name.
  - `Logger` singleton stores log entries containing level, message, and source-location metadata; tests verify storage, retrieval, and ordering of multiple logs.
  - `TestLogger` (derived from `SimpleLogger`) used to validate thread-safe accumulation of log strings via `std::ostringstream`.
  - Multi-threaded logging tests using `std::thread` and `std::jthread` to ensure messages from multiple concurrent workers are present and not lost or interleaved.
  - `MTLogger` test that writes to a provided `std::ostream` with locked output; tests verify each worker's messages appear in the captured stream.

## Test framework

- GoogleTest is used for all unit tests. Ensure the test runner links and executes GoogleTest to run these cases.

## C++ features used in this test project

- `std::source_location` (`<source_location>`) — tests assert presence of file/function/line metadata captured by default arguments.
- Threading primitives — `std::thread`, `std::jthread`, and synchronization via `std::mutex` / `std::scoped_lock`.
- Stream utilities — `std::ostringstream` for capturing and asserting on formatted log output.
- Standard containers and utilities — `std::vector`, `std::string`.
- GoogleTest macros and helpers (`TEST`, `EXPECT_NE`, `ASSERT_EQ`) and internal stdout capture utilities used in some test cases.

## Requirements

- C++20 compatible compiler and standard library with `<source_location>` and standard threading support.
- GoogleTest linked into the test runner.

## Notes

- Tests focus on verifying that call-site metadata is captured automatically and that logger implementations behave correctly under concurrent access.
- No usage examples are included in this README; run the test suite to observe concrete behavior and outputs.