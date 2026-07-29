# 10_LambdaImprovements

## Overview

This project demonstrates several improvements and patterns for lambda-based asynchronous and concurrent tasks in modern C++ (C++17). It includes multiple dispatcher implementations (fixed-thread cancellable dispatcher, priority-based dispatcher, and dynamic priority dispatcher) and small examples showing how to use lambdas with `std::async` and `std::packaged_task`.

## Features

- `CancellableTaskDispatcher`
  - A thread-pool based dispatcher that supports enqueuing tasks together with a cancellation token. Tasks check the provided `CancelToken` before starting and before execution to avoid running cancelled work. Returns `std::future` objects from enqueued tasks.
  - Thread-safe queue, worker threads, and graceful shutdown.

- `PriorityTaskDispatcher`
  - A fixed-size thread pool that schedules tasks based on `TaskPriority` (High, Normal, Low).
  - Tasks are wrapped in `std::packaged_task` and queued into a `std::priority_queue` to ensure higher-priority tasks are executed first.

- `DynamicPriorityTaskDispatcher`
  - A dispatcher that adjusts the number of worker threads between configured minimum and maximum based on queue demand.
  - Uses a priority queue of tasks to prefer higher-priority work while scaling workers dynamically.

- `LambdaAsyncTaskExample`
  - Small examples showing passing `std::unique_ptr` into lambda-captured async tasks via `std::async` and returning `std::future` results.

## Public API (summary)

- `CancellableTaskDispatcher`
  - Constructor: `CancellableTaskDispatcher(size_t threadCount = std::thread::hardware_concurrency())`
  - `template<typename Func, typename Token, typename... Args> auto enqueue(Func&& func, Token&& token, Args&&... args) -> std::future<ReturnType>`
  - Destructor stops workers and joins threads.
  - Relies on `CancelToken` (see `CancelToken.h`) which must provide an `isCancelled()` method.

- `PriorityTaskDispatcher`
  - Constructor: `PriorityTaskDispatcher(size_t threadCount = std::thread::hardware_concurrency())`
  - `template <typename F, typename... Args> auto enqueue(TaskPriority priority, F&& func, Args&&... args) -> std::future<RetType>`

- `DynamicPriorityTaskDispatcher`
  - Constructor: `DynamicPriorityTaskDispatcher(size_t minThreads = 2, size_t maxThreads = 8)`
  - Methods: `enqueue(Task task, int priority)`, `start()`, `stop()`, `getWorkerCount()`, `getQueueSize()`

- `LambdaAsyncTaskExample`
  - `static std::future<std::string> dispatchTask(std::unique_ptr<Task> task)`
  - `static std::vector<std::future<std::string>> dispatchMultipleTasks(std::vector<std::unique_ptr<Task>> tasks)`

## Requirements

- Visual Studio with C++17 support.
- No external libraries required; uses the C++ standard library threading and concurrency features.

## Building

Open the solution or the `10_LambdaImprovements` project in Visual Studio and build using the IDE. Select the desired configuration (Debug or Release) and platform, then build the project. The produced binaries will be in the project's output directory (for example, `Debug\` or `Release\`).

## Running

Use the provided examples or unit tests (if present) to exercise the dispatchers. The dispatchers run worker threads internally and print only diagnostic messages in error cases. Prefer writing small integration tests or sample programs that enqueue tasks and verify `std::future` results and cancellation behavior.

## Tests

If a corresponding test project exists (e.g., `10_LambdaImprovementsTest`), use Visual Studio's Test Explorer to run unit tests. Tests should validate:

- Task scheduling order for priority dispatchers.
- Worker scaling for the dynamic dispatcher.
- Cancellation handling for `CancellableTaskDispatcher` when `CancelToken` indicates cancellation.
- Correct `std::future` lifecycle and exception propagation for cancelled tasks.

## Notes and Caveats

- Ensure `CancelToken` lifetime outlives the task execution or is safely copied if necessary.
- Be cautious about exceptions thrown by tasks — `std::packaged_task` and `std::future` will propagate exceptions; dispatchers commonly catch exceptions at worker boundaries to prevent thread termination.
- The `DynamicPriorityTaskDispatcher` implementation must carefully synchronize worker creation and destruction to avoid races.

## License

See the repository `LICENSE` file for license details.