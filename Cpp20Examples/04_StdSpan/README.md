# 04_StdSpan

This project demonstrates the use of `std::span` for non-owning views over contiguous sequences. The header/source examples show common patterns for reading, slicing, and writing into existing containers and raw arrays without copying.

## Contents

- `04_StdSpan.h` / `04_StdSpan.cpp` — Implementations include:
  - `Sum(std::span<const int>)` — sums elements from any contiguous integer sequence.
  - `GetSubspan(std::span<const int>, size_t offset, size_t count)` — returns a subspan view referencing a slice of the input.
  - `ContainsChar(std::span<const char>, char target)` — checks for a character in a character span.
  - `SumMatrix(std::span<const int>)` — example of summing flattened matrix data provided as a span.
  - `PrintNumbers(std::span<const int>)` — outputs elements of a span to stdout.
  - `FillBuffer(std::span<int>, int value)` — demonstrates in-place modification of an existing buffer via a mutable span.
  - `PrintMatrix(std::span<int, 9>)` — example of a fixed-size span (extent) used to print a 3x3 matrix.

## C++20 features used

- `std::span` (`<span>`) — non-owning view over contiguous data with both bounded and dynamic extents.
- Fixed-size span specialization (`std::span<T, N>`) — compile-time extent used in `PrintMatrix`.
- Interoperability with built-in arrays, `std::array`, and `std::vector` — functions accept spans constructed from these containers without copying.
- Use of algorithms and utilities such as `std::accumulate` and `std::find` with span iterators.

## Requirements

- C++20 compatible compiler and standard library with `<span>` support.

## Testing

- Unit tests for this project are located in the sibling test project `04_StdSpanTest`. The tests use GoogleTest to validate behavior with arrays, vectors, std::array, and flattened matrix buffers.

## Notes

- `std::span` is a lightweight way to accept or expose contiguous sequences without enforcing ownership, improving API clarity and avoiding unnecessary allocations or copies.
- Functions that accept `std::span` are generic over the underlying container and can be called with arrays, `std::vector`, `std::array`, or raw pointers where appropriate.