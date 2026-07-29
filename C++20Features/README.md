# C++20Features

## Overview

This solution is a collection of focused C++20 examples and unit tests demonstrating language and standard library features introduced or improved in C++20. Each project is small and self-contained to illustrate a single feature or a related group of features.

Solution file: `C++20Features.sln`

Supported environment
- Visual Studio 2022 (recommended) or another C++20-capable toolchain.
- Projects are configured for MSVC; tests use GoogleTest (package included under `packages/`).

## How to build

1. Open `C++20Features.sln` in Visual Studio 2022.
2. Ensure C++ Language Standard is set to C++20 (Project Properties → C/C++ → __Language__ → __C++ Language Standard__).
3. Restore NuGet packages if prompted (GoogleTest package is included under `packages/`).
4. Build individual projects or the whole solution.

Alternatively, create a CMake target that sets `CMAKE_CXX_STANDARD` to 20 and add the desired projects.

## Projects (summary)

Each project folder contains a demonstration (`*.cpp`, `*.h`) and many projects include corresponding unit tests (`*Test` projects) using GoogleTest.

- `00_Concepts`  
  Demonstrates C++20 Concepts: user-defined concepts, standard concepts such as `std::integral` and `std::floating_point`, constrained templates, and overload resolution driven by concepts.

- `00_ConceptsTest`  
  GoogleTest unit tests verifying the concepts examples.

- `01_FinancialModule`  
  Small example showing modularized or library-style code for financial utilities.

- `01_ModulesApp`  
  Module / modularization example. Demonstrates module-style usage or modular compilation patterns.

- `01_ModulesTest`  
  Unit tests / examples exercising the modules code.

- `02_Ranges`  
  Demonstrates C++20 Ranges and Views: `std::views::filter`, `std::views::transform`, `std::ranges::count`, and `std::views::take` combined with algorithms.

- `02_RangesTest`  
  Tests for the Ranges examples (GoogleTest).

- `03_Coroutines`  
  Coroutines examples: a `Generator<T>` coroutine wrapper (promise type, handle management) with sequence, Fibonacci, and infinite generators using `co_yield`.

- `03_CoroutinesTest`  
  Tests validating coroutine generators and behavior.

- `04_Concurrency`  
  C++20 concurrency examples: `std::jthread` with `std::stop_token`, `std::latch`, and `std::barrier`, plus examples of atomic counters and thread coordination.

- `04_ConcurrencyTest`  
  Tests for concurrency examples.

- `05_Formatting`  
  Demonstrates `std::format` usage: basic formatting, numeric formatting (precision, binary), alignment and padding, and chrono/time formatting with `localtime_s` / `localtime_r` handling.

- `05_FormattingTest`  
  Tests for formatting examples.

- `06_ThreeWayComp`  
  Demonstrates the three-way comparison operator (`<=>`) and auto-generated `operator==` via defaulted spaceship operator.

- `06_ThreeWayCompTest`  
  Tests for three-way comparison examples.

- `07_DesignatedInit`  
  Shows C++20 designated initializers for aggregates and ordering rules.

- `07_DesignatedInitTest`  
  Tests for designated initializer examples.

- `08_Constexpr`  
  Examples showing enhancements to `constexpr` and compile-time evaluation.

- `08_ConstexprTest`  
  Tests verifying `constexpr` examples.

- `09_AtomicWait`  
  Demonstrates `std::atomic` wait/notify (`atomic::wait`, `atomic::notify_one`) for efficient blocking and notification patterns.

- `09_AtomicWaitTest`  
  Unit tests for atomic wait/notify examples.

- `10_SyncStreams`  
  Demonstrates `std::osyncstream` for synchronized output from multiple threads and safe vs unsafe printing behaviors.

- `10_SyncStreamsTest`  
  Tests showing expected synchronized output behavior.

## Notable files and layout

- `C++20Features.sln` — solution file listing all projects.
- Each project folder contains:
  - `*.vcxproj` — Visual Studio project file.
  - `pch.*` — precompiled header files used by examples.
  - `*.h`, `*.cpp` — example implementation.
  - `*Test` folders contain GoogleTest-based unit tests and `*.vcxproj`.

- `packages/` — includes the GoogleTest package used by test projects.

## Tests

All `*Test` projects use GoogleTest. Run tests from Visual Studio Test Explorer or run the test executables produced by the test projects.

## Contributing

- Keep examples small and focused.
- Follow C++20 idioms and clarity for educational purposes.
- If you add new examples, include a short test and update this README with a brief description.

## License

No license file is included by default. Add a `LICENSE` file if you intend to publish or share the repository.