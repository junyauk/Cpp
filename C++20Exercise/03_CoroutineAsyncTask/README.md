# 03_CoroutineAsyncTask

This project demonstrates Task-style coroutines in C++20, focusing on `co_return`, `co_await`, coroutine promises, awaiters, nested tasks, and simple continuation handling.

## Purpose

- Provide a minimal `Task<T>` coroutine type and supporting promise to illustrate async-style coroutines.
- Demonstrate how to implement awaitable semantics, continuation propagation, exception capture, and manual resume semantics.
- Show a simple awaiter (`DelayAwaiter`) and integration with a timer/continuation queue.

## Key files

- `Task.h`  
  - Implements `Task<T>` and `TaskPromise<T>`:
    - Promise stores result, exception pointer, and an optional continuation handle.
    - `get_return_object`, `initial_suspend`, `final_suspend`, `return_value`, and `unhandled_exception` are implemented to control lifecycle and error propagation.
    - `Task` provides `start_and_get_result()` and `operator co_await()` to support awaiting and retrieving results.
  - Implements `DelayAwaiter` demonstrating an awaiter that suspends and schedules continuation via a timer queue.

- `TimerQueue.h` (project helper)  
  - Provides timer/continuation registration used by `DelayAwaiter` to resume coroutines (project-specific helper; required for simulated delays).

## Tests

- `03_CoroutineAsyncTaskTest/CoroutineAsyncTaskTest.cpp`  
  - Exercises:
    - `co_return` and retrieving results via `start_and_get_result()`.
    - `co_await` with custom awaiter and nested tasks.
    - Exception propagation from coroutines to callers.
  - Uses GoogleTest for assertions.

## Demonstrated C++20 features

- Coroutines: `co_return`, `co_await`, custom `promise_type`, and `std::coroutine_handle`.
- Awaitable/awaiter pattern and continuation handling.
- Exception capture and rethrow via promise.
- Nested coroutines and parent/child continuation semantics.

## Requirements

- C++20-compliant compiler (MSVC in Visual Studio 2022, or recent GCC/Clang with `-std=c++20`).
- Visual Studio 2022 or a CMake-capable build environment.
- GoogleTest for running unit tests.

## Build notes

- Include `Task.h` and its helper headers in a C++20 target and set the language standard to C++20.
- Visual Studio: Project Properties Å® C/C++ Å® __Language__ Å® `C++ Language Standard` Å® __ISO C++20 Standard (/std:c++20)__.
- CMake: set `CMAKE_CXX_STANDARD=20`.
- Ensure `TimerQueue` implementation is available and linked for tests/examples that use `DelayAwaiter`.

## Notes

- The `Task` implementation here is educational and minimal; production async frameworks require more robust scheduling, synchronization, and lifetime management.
- Tests illustrate typical usage patterns. If you extend Task semantics, update tests accordingly.

## Contributing

Contributions welcome. Ensure changes compile with the C++20 toolchain and add/adjust tests as necessary.