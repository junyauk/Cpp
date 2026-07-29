# 03_Coroutines

## Overview

This project demonstrates C++20 coroutines through a compact generator implementation and a set of coroutine-based examples. The code shows how to implement a coroutine promise type, manage coroutine handles safely, and provide a simple generator interface that yields values lazily using `co_yield`.

## Requirements

- C++20-capable compiler (Visual Studio 2022 recommended).
- Project configured to use the C++20 language standard.

## Build

1. Open `C++20Features.sln` in Visual Studio 2022.  
2. Ensure the C++ Language Standard is set to C++20 (Project Properties → C/C++ → __Language__ → __C++ Language Standard__).  
3. Build the `03_Coroutines` project or the entire solution.

Precompiled headers (`pch.*`) are provided for convenience.

## Contents

- `Coroutines_Basic.h`  
  - Implements a minimal `Generator<T>` type and its `GeneratorPromise<T>` promise type.
  - Demonstrates:
    - `createSequenceGenerator(int start, int count)` — yields a finite sequence using `co_yield`.
    - `createFibonacciGenerator(int limit)` — yields Fibonacci numbers up to a limit.
    - `createInfiniteNumberGenerator(int start)` — yields an unbounded increasing sequence.
  - Proper handle management (RAII), move semantics for generator handles, and error handling in the promise type.

- `03_Coroutines.vcxproj` — Visual Studio project file.
- `pch.h` / `pch.cpp` — precompiled header support.

## Tests

- `03_CoroutinesTest` contains GoogleTest-based unit tests that validate generator behavior:
  - Correct values yielded by finite generators.
  - Empty sequence behavior.
  - Fibonacci sequence correctness.
  - Generator state preservation across resumptions.
  - External stopping of infinite generators (consumer-driven termination).

## Contributing

- Keep examples focused and minimal.
- When adding new coroutine examples, include unit tests in `03_CoroutinesTest`.
- Prefer clear lifetime and ownership semantics when exposing coroutine handles or generator interfaces.

## License

No license file is included by default. Add a `LICENSE` file if you intend to publish or share the repository.