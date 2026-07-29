# Exercises - ModernCpp_Mastery

This folder contains practical exercises demonstrating modern C++ features and design patterns. Each exercise focuses on specific aspects of contemporary C++ development.

---

## Exercise 01: Image Pipeline with Thread Pool

### Overview
A multi-threaded image processing pipeline that applies a series of filters to images using a custom thread pool. This exercise demonstrates advanced concurrency patterns, template metaprogramming, and type-safe filter composition.

### Objectives
- Implement a type-safe filter pipeline using C++ templates
- Build a custom thread pool with modern synchronization primitives
- Process images in parallel using work slicing and barriers
- Apply design patterns for extensible image filter chains

### Core Components

#### ImagePipeline (`image_pipeline.h`)
A compile-time validated pipeline that chains multiple image filters together. The pipeline:
- Uses **concepts** to enforce filter type compatibility at compile time
- Automatically generates intermediate buffer types via template metaprogramming
- Distributes work across threads using a work-stealing queue pattern
- Synchronizes filter stages with `std::barrier`

#### ThreadPool (`thread_pool.h`)
A thread pool implementation featuring:
- **`std::jthread`** for automatic thread lifetime management
- **`std::stop_token`** and **`std::stop_source`** for cooperative thread cancellation
- **`std::move_only_function`** to capture non-copyable callable objects
- **`std::packaged_task`** for asynchronous task execution with futures
- **`std::condition_variable_any`** for efficient thread synchronization

#### Pixel and Image Types (`pixel.h`, `image.h`)
- Type-safe pixel representations (GrayPixel, RgbaPixel, etc.)
- Flexible image storage using standard containers
- Support for image metadata and slice operations

#### Filters (`*_filter.h`)
Extensible filter implementations including:
- **GrayscaleFilter**: Converts color images to grayscale
- **SepiaFilter**: Applies sepia tone with multiple strategies (scalar, SIMD)
- **BlurFilter**: Kernel-based image blurring
- **EdgeFilter**: Edge detection algorithms
- **ThresholdFilter**: Binary image thresholding

### Modern C++ Features Used

| Feature | Purpose |
|---------|---------|
| **C++20 Concepts** | Type-safe constraint validation for filter chains |
| **Template Metaprogramming** | Compile-time buffer type generation and validation |
| **std::jthread** | RAII-based thread management with automatic cleanup |
| **std::stop_token / std::stop_source** | Cooperative cancellation for graceful thread shutdown |
| **std::move_only_function** | Non-copyable callable type storage in work queues |
| **std::packaged_task** | Type-erased task wrapping with result retrieval |
| **std::barrier** | Efficient multi-phase synchronization for pipeline stages |
| **std::condition_variable_any** | Synchronization with custom mutex types |
| **Perfect Forwarding** | Optimal parameter passing with `std::forward` |
| **std::future / std::promise** | Asynchronous result propagation |
| **CRTP (Curiously Recurring Template Pattern)** | Static polymorphism for filters |
| **mdspan (C++23)** | Multi-dimensional view semantics for image data |
| **std::invoke** | Type-erased function invocation |
| **Structured Bindings** | Convenient tuple and aggregate unpacking |

### Architecture Highlights

1. **Type Safety**: Compile-time validation ensures only compatible filters can be chained
2. **Memory Efficiency**: Minimal allocations through move semantics and perfect forwarding
3. **Thread Safety**: Atomic operations and condition variables prevent race conditions
4. **Extensibility**: CRTP-based filter design allows new filters without modifying the pipeline
5. **Performance**: Sliced processing and work distribution across CPU cores

---

## Exercise 02: Job System with Work Stealing

### Overview
A high-performance job scheduling system inspired by game engine architectures. This exercise focuses on task-based parallelism, work-stealing queues, and job dependencies.

### Objectives
- Design a scalable job scheduler for heterogeneous workloads
- Implement work-stealing queue for load balancing
- Support job dependencies and completion tracking
- Leverage modern C++ for zero-overhead abstractions

### Core Components

#### Job (`job.h`)
A move-only callable wrapper that:
- Uses **C++20 concepts** to validate callable signatures
- Captures function and arguments via **`std::bind_front`**
- Stores callables in **`std::move_only_function`** for non-copyable handlers
- Returns `void` to ensure job completion semantics

```cpp
template<typename F, typename... Args>
concept JobCallable = std::is_invocable_r_v<void, F, Args...>;
```

#### JobScheduler (`job_scheduler.h`)
Coordinates job execution across worker threads:
- Manages job queues and dependency tracking
- Distributes jobs to available worker threads
- Tracks completion status and results
- Handles priority and scheduling policies

#### WorkerThread (`worker_thread.h`)
Individual worker implementation featuring:
- Cooperative thread semantics with `std::jthread`
- Work-stealing from peer queues for load balancing
- Efficient wait strategies to minimize busy-waiting

#### WorkStealingQueue (`work_stealing_queue.h`)
A concurrent FIFO queue with stealing capabilities:
- Lock-free or low-lock operations
- Safe stealing from other threads' queues
- Efficient work distribution for load balancing

### Modern C++ Features Used

| Feature | Purpose |
|---------|---------|
| **C++20 Concepts** | Validate callable signatures at compile time |
| **std::bind_front** | Bind function arguments without type erasure |
| **std::move_only_function** | Type-safe non-copyable callable storage |
| **std::jthread** | RAII thread management with cancellation |
| **std::stop_token** | Cooperative cancellation signaling |
| **Perfect Forwarding** | Zero-copy parameter passing |
| **std::invoke / std::invoke_result_t** | Generic function invocation |
| **std::enable_if / std::enable_if_t** | Compile-time conditional overloads |
| **Structured Bindings** | Convenient unpacking of tuple results |
| **std::atomic** | Lock-free synchronization primitives |
| **Variadic Templates** | Flexible job argument handling |

---

## Exercise 03: SimpleLogger (Utility)

### Overview
A minimalist logging utility demonstrating RAII patterns and simple synchronization.

### Features
- Thread-safe log output with automatic synchronization
- Flexible message formatting
- Support for different log levels

### Modern C++ Features
- **std::lock_guard** / **std::scoped_lock**: RAII-based mutex locking
- **std::mutex**: Thread-safe critical section protection
- **std::string_view**: Non-owning string references
- **Variadic Templates**: Flexible argument handling

---

## Key Design Patterns

1. **CRTP (Curiously Recurring Template Pattern)**: Static polymorphism for filters
2. **Work Stealing**: Load-balanced task distribution
3. **RAII**: Resource management and automatic cleanup
4. **Zero-Cost Abstractions**: Compile-time type checking with no runtime overhead
5. **Move Semantics**: Efficient transfer of ownership
