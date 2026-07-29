# 01_ConceptsAndRangesTest

This test project validates the behavior and correctness of the `01_ConceptsAndRanges` implementations (`IProcessor`, `Cpp17Processor`, and `Cpp20Processor`) from `Combined_Processor.h`. The tests are intended to ensure functional parity between the C++17-style implementations and the C++20 ranges/concepts implementations and to exercise the behaviors described by the interface.

## Purpose

- Verify correctness of processing operations declared in `IProcessor`.
- Validate edge cases (empty ranges, small sizes, out-of-range inputs).
- Ensure `Cpp20Processor` meets the semantics expected by `Cpp17Processor` where applicable.
- Exercise template/concept-constrained member functions where practical.

## Recommended test cases

- `process_and_sum`
  - Filter by threshold and sum results.
  - Cases: no matches, all matches, mixed values.

- `process_drop_reverse_sum`
  - Verify sorting, dropping first two elements, and reverse-sum behavior.
  - Cases: less than two elements, exactly two elements, many elements with duplicates.

- `process_and_check_size`
  - Test move semantics and returned size computation.
  - Cases: empty vector, size odd/even.

- `filter_and_output`
  - Validate filtering by `tag` and correct output container size.
  - Cases: tag not present, multiple matches.

- `process_and_find_index`
  - Test find behavior and index correctness.
  - Cases: element present at various positions, not found (expect -1).

- `process_and_concat`
  - Validate concatenation and out_of_range behavior when `min_count` not met.

- `process_and_slice`
  - Verify slicing (exclude first/last) and max-element limiting behavior.
  - Cases: size < 3, size == 3, size > limit.

- `process_bidirectional_stride_sum`
  - Validate stride summation (even-indexed elements) using bidirectional scanning.

- Concept- and template-specific behavior
  - Where possible, add tests that exercise `Cpp20Processor` template helpers (e.g., `count_unique_elements`, `find_index`, `concatenate_and_count`, `slice_and_count`) with appropriate input types to ensure constraints are satisfied.

## Files under test

- `01_ConceptsAndRanges/Combined_Processor.h` — contains `DataEntry`, `IProcessor`, `Cpp17Processor`, and `Cpp20Processor`.

## Dependencies

- GoogleTest (recommended) or another C++ unit test framework.
- C++20 compiler (MSVC in Visual Studio 2022, or GCC/Clang with `-std=c++20`).

## Build & Run

- Ensure the test project links against GoogleTest and includes the project header path for `01_ConceptsAndRanges`.
- Set the C++ standard to C++20:
  - Visual Studio: Project Properties → C/C++ → __Language__ → `C++ Language Standard` → __ISO C++20 Standard (/std:c++20)__.
  - CMake: set `CMAKE_CXX_STANDARD=20`.
- Run the test executable with the chosen test runner.

## Notes

- Prefer small, deterministic test vectors that clearly assert expected numeric results and container sizes.
- Add tests for both `Cpp17Processor` and `Cpp20Processor` and compare outputs to ensure parity.
- If new processing functions are added to `IProcessor`, extend the test suite accordingly.

## Contributing

- Add tests following the project conventions.
- Ensure tests compile and run under the C++20 toolchain.