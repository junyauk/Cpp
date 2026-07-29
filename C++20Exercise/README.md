# C++20Exercise

This solution contains C++20-focused sample code and exercises demonstrating modern C++ features (concepts, coroutines, ranges, and async/task patterns).

## Detected projects (Solution Explorer)

- `01_ConceptsAndRanges/`
  - Purpose: Compare C++17-style algorithms with C++20 ranges and concepts.
  - Key file: `01_ConceptsAndRanges/Combined_Processor.h`
  - Main types and features:
    - `DataEntry` (POD with `id`, `value`, `tag`, uses `operator<=>`).
    - `IProcessor` interface and two implementations:
      - `Cpp17Processor` — iterator/algorithm-based implementations.
      - `Cpp20Processor` — uses `std::ranges`, views, and C++20 concepts.
    - Demonstrates concepts (`NumericRange`, `SortableRange`, etc.), views (`filter`, `transform`, `drop`, `reverse`, `take`), and `std::ranges` algorithms.

- `02_CoroutineGenerator/`
  - Purpose: Generator-style coroutines using `co_yield`.
  - Key file: `02_CoroutineGenerator/NumberGenerator.h`
  - Main features:
    - `Generator<T>`-based producers (primes, non-primes, Fibonacci, alternating sequences, even numbers).
    - Use of concepts (`IntegralArgument`) and coroutine iterator integration with ranges and STL algorithms.

- `02_CoroutineGeneratorTest/`
  - Purpose: Unit tests for coroutine generators (GoogleTest).
  - Key file: `02_CoroutineGeneratorTest/CoroutineGeneratorTest.cpp`
  - Tests demonstrate correctness and iterator/sequence behavior (prime generation, state preservation, composite sequences, alternating generation, filtered yields).

- `03_CoroutineAsyncTask/`
  - Purpose: Task-style coroutines demonstrating `co_return`, `co_await`, nested tasks and awaiters.
  - Key file: `03_CoroutineAsyncTask/Task.h`
  - Main features:
    - `Task<T>` and `TaskPromise<T>` implementing coroutine promise/awaitable semantics.
    - `DelayAwaiter` and simple timer/continuation handling (uses a `TimerQueue` helper in the project).
    - Demonstrates nesting (`co_await` child tasks), exception propagation via promise, and manual resume semantics.

- `03_CoroutineAsyncTaskTest/`
  - Purpose: Unit tests for async/task coroutine exercises (GoogleTest).
  - Key file: `03_CoroutineAsyncTaskTest/CoroutineAsyncTaskTest.cpp`
  - Tests cover `co_return` behavior, awaiting with `DelayAwaiter`, nested tasks, and exception handling.

Note: `01_ConceptsAndRangesTest` was not found in the workspace during detection.

## Requirements

- C++20-compliant compiler (MSVC in Visual Studio 2022, or recent GCC/Clang with `-std=c++20`)
- Visual Studio 2022 or a CMake-capable build environment
- GoogleTest for the test projects (used in detected `*Test` projects)

## Build & Run

- Visual Studio:
  - Open the solution or include the projects in a solution.
  - Ensure the language standard is set to C++20:
    - __Project Properties > C/C++ > Language__ → set `C++ Language Standard` to __ISO C++20 Standard (/std:c++20)__.
- CMake:
  - Configure with a C++20 toolchain and set `CMAKE_CXX_STANDARD=20` if required.
- Tests:
  - Build the `*Test` projects and run with the configured GoogleTest runner.

## Notes

- The code is header-centric for easy inclusion into small test harnesses and samples.
- The README reflects the filesystem at detection time; if you add or remove projects (for example, add `01_ConceptsAndRangesTest`), regenerate the README to reflect updates.

## Contributing

Contributions are welcome. Please ensure code compiles with C++20 and follow repository conventions.

## License

Specify the project license here if applicable.
