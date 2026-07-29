# Cpp20Examples

A collection of concise, focused C++20 example projects that demonstrate language and library features introduced or improved in C++20. Each example is intentionally compact and header/source-oriented for study and testing.

## Projects

- `01_ConceptsBasics` — C++20 Concepts: user-defined and standard concepts, constrained templates, requires-clauses, and constrained overloads.
- `01_ConceptsBasics_Test` — GoogleTest unit tests validating the Concepts examples and providing concrete usage scenarios.

- `02_RangesAndViews` — Ranges and Views: composing `filter`, `transform`, `take`, `drop`, `iota`, and materializing or aggregating view results.
- `02_RangesAndViewsTest` — Tests that materialize views and assert expected sequences and aggregated values.

- `03_StdFormat` — `std::format` usage: formatting text, numbers, and `std::chrono` date/time values with format specifiers, alignment, padding, and numeric bases.
- `03_StdFormatTest` — Tests validating formatted strings and chrono-format patterns.

- `04_StdSpan` — `std::span` examples: non-owning views over contiguous data, subspans, fixed-size extents, and in-place modification.
- `04_StdSpanTest` — Tests exercising span interoperability with arrays, `std::vector`, and `std::array`.

- `05_ThreeWayComparison` — Three-way comparison (`operator<=>`), `std::strong_ordering`, `std::partial_ordering`, defaulted and custom spaceship operators.
- `05_ThreeWayComparisonTest` — Tests verifying ordering semantics, equality, and special floating-point cases (NaN).

- `06_JthreadStopToken` — `std::jthread` and stop-token cooperative cancellation: worker classes, thread pool, `std::stop_token`, and `std::stop_source` usage.
- `06_JthreadStopTokenTest` — Tests for start/stop behavior, cooperative cancellation, and thread-pool shutdown.

- `07_SourceLocation` — `std::source_location` integration in logging APIs to capture call-site file, function, line, and column information; thread-safe logger examples.
- `07_SourceLocationTest` — Tests asserting presence of call-site metadata and thread-safe logging behavior.

- `08_ConstexprAdvanced` — Advanced compile-time computation: `constexpr` and `consteval` functions and templates, compile-time `sum`, `factorial`, `gcd`, and string-length utilities.
- `08_ConstexprAdvancedTest` — Tests combining `static_assert` compile-time checks and runtime assertions.

- `09_CoroutinesBasics` — Coroutine primitives: generators (`co_yield`), resumable tasks, custom awaiters, `co_await`, and async resume examples using `std::coroutine_handle` and promise types.
- `09_CoroutinesBasicsTest` — Tests validating generator iteration, awaiter behavior, and coroutine lifecycle semantics.

- `TestUtilities` — Small header-only helpers used by tests (e.g., stdout capture helper).

## C++20 features used across the solution

- Concepts and constrained templates (`<concepts>`, `requires`, abbreviated function templates).
- Ranges and Views (`<ranges>`, views like `filter`, `transform`, `take`, `drop`, `iota`).
- Text formatting with `std::format` (`<format>`) and chrono format specifiers.
- `std::span` for non-owning views over contiguous sequences.
- Three-way comparison (`operator<=>`, `<compare>`, `std::strong_ordering`, `std::partial_ordering`).
- `std::jthread`, `std::stop_token`, `std::stop_source` for cooperative cancellation and stop-token-aware waiting.
- `std::source_location` for call-site diagnostics.
- `constexpr` and `consteval` for compile-time evaluation.
- Coroutines (`co_await`, `co_yield`, `<coroutine>`, custom awaiters, `std::coroutine_handle`).
- `std::optional`, `std::numbers`, `std::chrono`, and other standard utilities.

## Requirements

- A C++20-compliant compiler and standard library with support for the features used (Concepts, Ranges, `std::format`, `std::span`, `std::jthread`/stop token, `std::source_location`, coroutines, etc.).
- GoogleTest for running unit tests included in sibling `*_Test` projects.

## Running tests

- Each example project has a corresponding test project (`<N>_..._Test`) using GoogleTest. Build and run the test executables to verify behavior and to inspect concrete usage patterns used by the tests.

## Notes

- Examples are intentionally small and focused on demonstrating language/library idioms rather than production-quality APIs.
- The README files inside each project contain more targeted descriptions and lists of features used per-project.
- No usage examples are included in this top-level README; consult the tests for concrete usage and validation.