# 05_ThreeWayComparison

This project demonstrates C++20 three-way comparison (the "spaceship" operator) and related ordering/ comparison utilities. The examples show defaulted and custom `operator<=>` implementations, use of the standard ordering types, and how three-way comparisons interact with equality operators.

## Contents

- `05_ThreeWayComparison.h` / `05_ThreeWayComparison.cpp` — Implementations include:
  - `Person` — a struct with a defaulted `operator<=>` producing `std::strong_ordering` and automatic equality.
  - `Point` — a struct with a manually implemented `operator<=>` that compares `x` first then `y`, returning `std::strong_ordering`; `operator==` is defaulted.
  - `CompareAges` — demonstrates comparing two `Person` objects using `operator<=>` and mapping `std::strong_ordering` to integer results (-1, 0, 1).
  - `CompareInts` — uses the three-way comparison on integers and formats the result into a human-readable string.
  - `CompareDoubles` — demonstrates `std::partial_ordering` for floating-point comparisons (handles unordered results such as NaN).

## C++20 features used

- Three-way comparison operator (`operator<=>`) — defaulted and custom implementations.
- Standard ordering categories — `std::strong_ordering`, `std::partial_ordering`.
- Defaulted comparisons (`= default`) for `operator<=>` and `operator==`.
- The `<compare>` header to access ordering types and the spaceship operator semantics.
- Interaction between built-in three-way comparisons and user-defined comparisons.

## Requirements

- C++20 compatible compiler and standard library with support for three-way comparison and `<compare>`.

## Testing

- Unit tests for this project are located in the sibling test project `05_ThreeWayComparisonTest`. The tests use GoogleTest to validate relational operators, ordering results, and behavior with special floating-point values (e.g., NaN).

## Notes

- `std::strong_ordering` is appropriate for types with a total ordering (e.g., integers, user types with total order). `std::partial_ordering` is used for types like floating-point values where unordered comparisons (NaN) can occur.
- The examples are concise and intended for studying the semantics and usage patterns of C++20 three-way comparison.