# 02_CoroutineGenerator

This project demonstrates generator-style coroutines in C++20 using `co_yield`. It provides a compact `Generator<T>` coroutine type and several example generators that produce sequences such as primes, Fibonacci, alternating sequences, and filtered numeric sequences.

## Key files

- `Generator.h`  
  - Implements a minimal `Generator<T>` coroutine type with `promise_type`, an input iterator, and range support.
  - Marks `Generator<T>` as a borrowed range to enable integration with range-based for and STL/Ranges algorithms.

- `NumberGenerator.h`  
  - Implements concrete producers using `Generator<T>`:
    - `generate_primes_up_to(...)`
    - `generate_closest_non_primes(...)`
    - `generate_fibonacci(...)`
    - `generate_alternating(...)`
    - `generate_even_numbers_up_to(...)`
  - Demonstrates coroutine state preservation, templates constrained by concepts, and integration with `std::ranges`/STL algorithms.

## Demonstrated C++20 features

- Coroutines (`co_yield`, `co_return`, `std::coroutine_handle`, custom `promise_type`)
- Generator pattern with iterator integration (range-based for compatibility)
- Concepts for template constraints (e.g., `IntegralArgument`)
- Interoperation with Ranges and Views (`std::views::filter`, `std::accumulate`, etc.)

## Tests

- Corresponding test project: `02_CoroutineGeneratorTest`  
  - Key file: `02_CoroutineGeneratorTest/CoroutineGeneratorTest.cpp`  
  - Tests cover correctness (prime generation, Fibonacci), state preservation across partial iteration, alternating sequence composition, and filtered yields.
  - Tests use GoogleTest.

## Requirements

- C++20-compliant compiler (MSVC in Visual Studio 2022, or recent GCC/Clang with `-std=c++20`)
- Visual Studio 2022 or a CMake-capable build environment
- GoogleTest for the test project

## Build notes

- The generator utilities are header-only. Include `Generator.h` and `NumberGenerator.h` in a C++20 project and set the language standard to C++20.
- Visual Studio: Project Properties Å® C/C++ Å® __Language__ Å® set `C++ Language Standard` to __ISO C++20 Standard (/std:c++20)__.
- CMake: set `CMAKE_CXX_STANDARD=20`.

## Notes

- `Generator<T>` resumes the coroutine upon iterator construction and supports typical range-based for loops and simple range algorithms.
- Keep generator functions simple and deterministic for reliable testing.
- If you extend the project, add tests in `02_CoroutineGeneratorTest` to validate stateful behavior and iterator semantics.

## Contributing

Contributions are welcome. Ensure all additions compile with the C++20 toolchain and include or update tests as appropriate.