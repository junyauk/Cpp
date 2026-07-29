# 02_CoroutineGeneratorTest

This test project verifies the behavior and correctness of the coroutine generators provided by the `02_CoroutineGenerator` project. Tests exercise generator semantics, state preservation, and interoperability with the STL/Ranges algorithms.

## Key file

- `02_CoroutineGeneratorTest/CoroutineGeneratorTest.cpp`  
  - Tests include:
    - Prime generation correctness (`generate_primes_up_to`)
    - State preservation across partial iteration (`generate_closest_non_primes`)
    - Fibonacci generation and ranges integration (`generate_fibonacci`)
    - Alternating sequence composition (`generate_alternating`)
    - Conditional yield / filtered generator (`generate_even_numbers_up_to`)

## Purpose

- Validate correctness and deterministic behavior of `Generator<T>`-based producers.
- Ensure generator iterators integrate with range-based for, `std::ranges` views, and STL algorithms.
- Confirm edge-case handling and sequence composition semantics.

## Dependencies

- GoogleTest (used by the test executable)
- Header dependencies: `Generator.h`, `NumberGenerator.h` from `02_CoroutineGenerator`
- C++20-compliant toolchain

## Requirements

- C++20 compiler (MSVC in Visual Studio 2022, or recent GCC/Clang with `-std=c++20`)
- GoogleTest library available to the test project

## Build & Run

- Visual Studio:
  - Open the test project and ensure the language standard is set to C++20:
    - __Project Properties > C/C++ > Language__ → __C++ Language Standard__ → __ISO C++20 Standard (/std:c++20)__.
  - Link the project with GoogleTest and run the test runner.

- CMake:
  - Ensure `CMAKE_CXX_STANDARD=20` and GoogleTest is discoverable/linked.
  - Build and run the produced test executable.

## Notes

- Tests use small deterministic datasets—prefer similar patterns when adding new tests.
- If generator implementations change, update or extend tests to cover new behaviors.

## Contributing

- Add tests under this project following existing patterns.
- Ensure all tests compile and pass with the C++20 toolchain before submitting changes.