# 10_LambdaImprovementsTest

## Overview

This test project contains unit tests for the `10_LambdaImprovements` examples. Tests are implemented using Google Test and exercise task dispatchers and lambda-based async helpers for correctness, concurrency, and cancellation behavior.

## Requirements

- Visual Studio with C++17 support (MSVC toolset compatible with C++17).
- Google Test integrated into the test project (gtest headers are used by the test sources).

## Building

Open the solution or the `10_LambdaImprovementsTest` project in Visual Studio and build the solution. Ensure the test project compiles successfully.

## Running Tests

- Use Visual Studio's __Test Explorer__ to discover and run the tests.
- Alternatively, run the produced test executable from the test project's output directory (for example, `Debug\` or `Release\`) to run all tests from the command line.

## Tests included

- `CancellableTaskDispatcherTests` (`CancellableTaskDispatcherTest.cpp`)
  - `TaskRunsNormally` — enqueues a simple task and verifies the returned `std::future` result.
  - `TaskCanBeCancelled` — verifies that cancelling the provided `CancelToken` causes the enqueued task to throw a cancellation exception before execution.
  - `TaskExceptionPropagates` — verifies that exceptions thrown inside tasks propagate through the `std::future`.

- `PriorityTaskDispatcherTest` (`PriorityTaskDispatcherTest.cpp`)
  - `TasksRunInPriorityOrder` — enqueues tasks with Low/Normal/High priorities and verifies execution order (High → Normal → Low).

- `LambdaAsyncTaskExample` tests (`LambdaAsyncTaskExampleTest.cpp`)
  - `SingleTaskRunsSuccessfully` — dispatch a single async task capturing a `std::unique_ptr` and verify completion.
  - `MultipleTasksRunConcurrently` — dispatch multiple tasks and verify returned names.
  - `CannotReuseMovedTask` — ensure moved `std::unique_ptr` is null after dispatch and task result is still retrievable.

## Notes

- Tests rely on proper `CancelToken` semantics; ensure the `CancelToken` implementation is used correctly and its lifetime outlives enqueued tasks when appropriate.
- Dispatcher implementations catch exceptions at thread boundaries to avoid terminating worker threads; exceptions are delivered via `std::future` returned to callers.
- The tests assume the environment supports threading and timing (sleep durations used in cancellation test).

## License

See the repository `LICENSE` file for license details.