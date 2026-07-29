# 03_CoroutineAsyncTaskTest

This test project verifies the behavior of the `03_CoroutineAsyncTask` examples. It exercises Task-style coroutines, awaiting semantics, nested tasks, and exception propagation using unit tests.

## Key file

- `03_CoroutineAsyncTaskTest/CoroutineAsyncTaskTest.cpp`  
  - Tests include:
    - `A_CoroutineReturnTest` — verifies `co_return` and retrieving results via `Task::start_and_get_result()`.
    - `B_CoroutineAwaitTest` — verifies awaiting with `DelayAwaiter` and integration with `Task`.
    - `C_NestedTaskTest` — verifies nesting (`co_await` on sub-tasks) and continuation propagation.
    - `D_ExceptionHandlingTest` — verifies exception propagation from coroutine to caller.

## Purpose

- Validate minimal `Task<T>`/`TaskPromise<T>` semantics implemented in the project.
- Ensure `operator co_await()` and `start_and_get_result()` behave correctly for synchronous test execution.
- Verify custom awaiter (`DelayAwaiter`) interaction with the test harness and timer queue.
- Confirm exception capture and rethrow via coroutine promise.

## Dependencies

- GoogleTest (used by the test executable)
- `Task.h`, `DelayAwaiter` and `TimerQueue.h` from `03_CoroutineAsyncTask`
- C++20 toolchain (compiler supporting C++20 coroutines)

## Requirements

- C++20-compliant compiler (MSVC in Visual Studio 2022, or recent GCC/Clang with `-std=c++20`)
- GoogleTest available to the test project

## Build & Run

- Visual Studio:
  - Open the test project, ensure the language standard is set to C++20:
    - __Project Properties > C/C++ > Language__ → __C++ Language Standard__ → __ISO C++20 Standard (/std:c++20)__.
  - Link with GoogleTest and run the test runner.

- CMake:
  - Ensure `CMAKE_CXX_STANDARD=20` and that GoogleTest is discoverable and linked.
  - Build and execute the test binary.

## Notes

- The `Task`/`TaskPromise` implementation in this project is educational/minimal. Production async systems need robust scheduling and lifetime management.
- Tests use simulated delays via `DelayAwaiter` and `TimerQueue`—ensure `TimerQueue` is available when running tests.
- If you extend task semantics or add awaiters, extend the tests accordingly.

## Contributing

- Add or update tests under this project to cover new behaviors.
- Ensure tests compile and pass under the C++20 toolchain before submitting changes.