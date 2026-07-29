# 07_SourceLocation

This project demonstrates C++20 source-location utilities and simple, thread-safe logging patterns that capture file, function, line and column information at the call site. The examples illustrate how `std::source_location` can be integrated into logging APIs to improve diagnostics and reduce manual location reporting.

## Contents

- `07_SourceLocation.h` — Header-only utilities including:
  - `logMessage` — free function that prints a message together with source location information (file, function, line, column) using `std::source_location::current()` as the default argument.
  - `Logger` — singleton-style logger that stores log entries with level and source-location metadata; thread-safe via `std::mutex`.
  - `SimpleLogger` / `TestLogger` — lightweight logger base and test subclass demonstrating scoped locking for multi-threaded logging.
  - `MTLogger` — multi-threaded logger writing to a provided `std::ostream` with locked output to avoid interleaving.

## C++20 features used

- `std::source_location` (`<source_location>`) — capture caller file name, function name, line and column; used with default argument `std::source_location::current()` to record call-site information automatically.
- Defaulted function parameter with `std::source_location::current()` — concise capture of call-site metadata.
- Thread-safety primitives (`std::mutex`, `std::scoped_lock`) used to protect logger state in concurrent scenarios.
- Integration with modern test and threading utilities (tests exercise behavior using `std::thread` and `std::jthread`).

## Requirements

- C++20 compatible compiler and standard library with support for `<source_location>`.
- Standard threading and synchronization support for multi-threaded test cases.

## Testing

- Unit tests are located in the sibling test project `07_SourceLocationTest`. Tests verify:
  - `logMessage` outputs the provided message and includes function and file name information.
  - `Logger` stores log lines containing level, message and source-location metadata.
  - Multi-threaded logging scenarios produce complete, non-interleaved log entries (tested via `TestLogger` and `MTLogger`).

## Notes

- `std::source_location` provides zero-cost or low-cost call-site metadata capture in most standard implementations; prefer using the `current()` default parameter to avoid callers having to pass location explicitly.
- Logger implementations here focus on illustrating integration with `std::source_location` and thread-safety; they are intentionally compact for study and testing.
- No usage examples are included in this README. Refer to the test project for concrete validation and usage patterns.