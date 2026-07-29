# 09_CoroutinesBasics

This project demonstrates C++20 coroutine basics through compact header-only examples. It covers generator-style coroutines, resumable tasks, custom awaiters, awaitable task wrappers, and simple composition patterns that illustrate how coroutines interact with promise types and coroutine handles.

## Contents

- `Generator.h` — a template `Generator<T>` implementing a coroutine-based generator using `co_yield`. Includes a sample `count_up_to` generator that yields integers.
- `CoYieldSample.h` — generator utilities demonstrating `co_yield` with iterator-style consumption, a Fibonacci generator, file-line streaming with `co_yield`, and a `flatten` template that yields items from nested containers.
- `TaskTemplate.h` — several coroutine task templates:
  - `Task<T>` — a simple value-returning coroutine wrapper with `get()` to resume and retrieve results.
  - `TaskCoAwait<T>` — an awaitable task showing custom `await_ready`, `await_suspend`, and `await_resume` semantics for `co_await`.
  - `TaskVoid` — void-return coroutine type used to demonstrate `co_await` usage in sample flows.
  - Example coroutine producers and small runner functions.
- `AsyncTask.h` — examples of asynchronous-style coroutines with custom awaiters:
  - `AsyncTask` and `Task` wrappers that manage `std::coroutine_handle`.
  - `SleepAwaiter` — a custom awaiter that resumes a coroutine after sleeping on a detached thread.
  - `RandomAwaiter` — a custom awaiter demonstrating `await_ready`, `await_suspend`, and `await_resume`.
  - Example `asyncFunction` and `randomCoroutine` that print lifecycle messages.
- Other support headers (e.g., `TaskTemplate.h` variants and samples) illustrating coroutine chaining, `co_return`, and interaction with `std::optional` and `std::coroutine_handle`.

## C++20 features used

- Coroutines language support — `co_await`, `co_yield`, `co_return`.
- `<coroutine>` types — `std::coroutine_handle<>`, custom `promise_type` definitions, and coroutine lifecycle management.
- Custom awaiters — types implementing `await_ready`, `await_suspend`, and `await_resume`.
- Generator patterns — implementing lazy sequence generators via `co_yield` and promise state (e.g., `std::optional` for current value).
- Resumable tasks and promise-based result propagation — value-returning and void-returning coroutine wrappers.
- Interaction with threading primitives — detached threads used inside awaiters to resume coroutines asynchronously.
- Move-only coroutine wrapper types and RAII coroutine destruction (`handle.destroy()` in destructors).

## Requirements

- C++20 compatible compiler and standard library with coroutine support (`<coroutine>`).
- Threading support for examples that resume coroutines from other threads.

## Testing

- Sibling test project (e.g., `09_CoroutinesBasicsTest`) contains unit tests that validate generator iteration, task resumption, awaiter behavior, and observable side effects produced by sample coroutines.

## Notes

- Examples are intentionally compact to illustrate core coroutine mechanics; production coroutine libraries often provide richer lifetime, scheduling, and synchronization abstractions.
- Many examples use move-only coroutine wrapper types; ensure correct lifetime management (destruction and destruction-time `handle.destroy()`).
- No usage examples are included in this README. Refer to the test project for concrete test-driven usages and behaviors.