# 09_CoroutinesBasicsTest

This test project contains GoogleTest unit tests that validate the coroutine examples in the sibling `09_CoroutinesBasics` project. The tests exercise generator-style coroutines, resumable task wrappers, custom awaiters, and asynchronous resumption behaviors to ensure correct sequencing, result propagation, and observable side effects.

## Contents

- Test cases validate behavior for:
  - Generator iteration and sequence production (e.g., `Generator<int>`, `count_up_to`, Fibonacci generator).
  - `co_yield`-based producers and iterator-style consumption (from `CoYieldSample.h` / `Generator.h`).
  - Resumable task wrappers (`Task<T>`, `TaskCoAwait<T>`, `TaskVoid`) including `get()` semantics and move-only lifetime handling (from `TaskTemplate.h`).
  - Custom awaiters (`SleepAwaiter`, `RandomAwaiter`) used by `AsyncTask` and `randomCoroutine` to verify await semantics (`await_ready`, `await_suspend`, `await_resume`) and asynchronous resumption.
  - Interaction between coroutines and threads when awaiters resume coroutines from other threads.
  - Correct destruction and cleanup of coroutine handles (RAII `destroy()` behavior).

## Test framework

- GoogleTest is used for unit tests. Ensure that the test runner links and runs GoogleTest to execute the suite.

## C++20 features used in the test project

- Coroutines language support — `co_await`, `co_yield`, `co_return`.
- `<coroutine>` types — `std::coroutine_handle<>`, custom `promise_type` implementations and lifecycle management.
- Custom awaiters implementing `await_ready`, `await_suspend`, and `await_resume`.
- Move-only coroutine wrapper types and RAII-based coroutine destruction (`handle.destroy()`).
- Interaction with threading APIs (`std::thread`) for awaiter-driven asynchronous resume semantics.
- `std::optional` and other standard utilities used in promise state and result propagation.

## Requirements

- C++20 compatible compiler and standard library with coroutine support (`<coroutine>`).
- Threading support for tests that exercise asynchronous awaiters.
- GoogleTest linked into the test runner.

## Notes

- Tests focus on protocol correctness (yield/resume/await lifecycle), result propagation, and safe cleanup of coroutine resources.
- No usage examples are included in this README; run the test suite to observe concrete behaviors and validation scenarios.