# 02_RangesAndViews

This project demonstrates C++20 Ranges and Views through compact header-only utilities that process standard containers with lazy, composable view adapters. The examples illustrate filtering, transforming, taking/dropping elements, combining views, and converting view results into concrete containers or aggregated values.

## Contents

- `02_RangesAndViews.h` — Header-only examples implementing the following utilities:
  - `filterEven` — returns a view filtering even integers from a `std::vector<int>`.
  - `squareAll` — returns a view that maps each element to its square.
  - `evenSquares` — composes a filter and transform to produce squares of even numbers.
  - `filterOddLessThanTen` — composes multiple filters and `take(5)` then materializes the results into a `std::vector<int>`.
  - `dropFirstThreeAndToString` — drops the first three elements, transforms remaining integers to `std::string`, and concatenates them with spaces using `std::accumulate`.
  - `enumerate` — creates a materialized `std::vector<std::pair<int, T>>` pairing indices with elements using `std::views::iota`.
  - `filterAndSquareOptional` — demonstrates transforming elements into `std::optional<int>`, filtering out empty optionals, then unwrapping values via chained views. This function is constrained with `std::ranges::input_range` and `requires std::convertible_to` on the range value type.
  - `printRange` — utility to print elements of any range to stdout.

## C++20 features used

- Ranges library (`<ranges>`) — view adapters and range utilities throughout the header.
- Views composability — `std::ranges::views::filter`, `transform`, `take`, `drop` and `std::views::iota`.
- Lazy views and adaptor chaining — functions return view expressions that are lazily evaluated until iterated or materialized.
- Concepts and constrained templates — `std::ranges::input_range` and `requires std::convertible_to<...>` used on template `filterAndSquareOptional`.
- Abbreviated function templates / deduced return types — functions returning auto views.
- `std::optional` for representing conditional results in view transformations.
- Use of `std::accumulate` with view iterators and `std::next` to aggregate transformed strings.

## Requirements

- C++20 compatible compiler and standard library with Range support.

## Testing

- Unit tests for this project are located in the sibling test project `02_RangesAndViewsTest`. The tests use GoogleTest to validate behavior by materializing view results and comparing expected vectors or strings.

## Notes

- Many functions return lazy views; to obtain a concrete container, materialize the view by iterating, copying into a container, or using algorithms that consume ranges.
- The code demonstrates idiomatic C++20 range composition and is intended as a concise reference for common view patterns.