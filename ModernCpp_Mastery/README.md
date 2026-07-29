# ModernCpp_Mastery - Comprehensive C++ Learning Solution

A comprehensive, hands-on learning platform for mastering modern C++ (C++17, C++20, C++23) through practical exercises, rigorous testing, and performance benchmarking.

---

## 📚 Overview

ModernCpp_Mastery is a multi-project Visual Studio solution designed to teach contemporary C++ development through real-world scenarios. Each exercise builds practical skills in:

- **Advanced Concurrency**: Thread pools, job scheduling, work-stealing
- **Type-Safe Design**: Concepts, template metaprogramming, CRTP
- **Zero-Cost Abstractions**: Move semantics, perfect forwarding, compile-time validation
- **Modern Synchronization**: std::jthread, std::barrier, std::stop_token
- **Performance**: Parallelization, SIMD optimization, cache-aware algorithms

This is **not just theory**—each exercise is:
- ✅ Fully implemented and tested
- ✅ Benchmarked for performance
- ✅ Documented with code examples
- ✅ Extensible for learning modifications

---

## 🏗️ Solution Architecture

```
ModernCpp_Mastery/
├── Exercises/                    # Implementation exercises
│   ├── Ex01_ImagePipeline/      # Multi-threaded image processing
│   ├── Ex02_JobSystem/          # Job scheduling with work-stealing
│   ├── SimpleLogger/            # RAII logging utility
│   └── README.md                # Exercise documentation
│
├── Tests/                        # Comprehensive test suite (Google Test)
│   ├── Ex01_ImagePipeline/
│   ├── Ex02_JobSystem/
│   └── README.md                # Testing documentation
│
├── Benchmarks/                   # Performance benchmarking (Google Benchmark)
│   ├── Ex01_ImagePipeline/
│   └── README.md                # Benchmarking documentation
│
├── ModernCpp_Mastery.sln        # Visual Studio solution file
└── README.md                    # This file
```

---

## 📋 Project Organization

### **Exercises Project**
Practical implementations demonstrating modern C++ patterns:

| Exercise | Focus | Key Features |
|----------|-------|--------------|
| **Ex01: Image Pipeline** | Concurrency & Type Safety | Thread pool, std::jthread, concepts, CRTP, template metaprogramming |
| **Ex02: Job System** | Task Parallelism | Job scheduling, work-stealing, std::move_only_function, concepts |
| **SimpleLogger** | RAII Patterns | Thread-safe logging, synchronization primitives |

➡️ **Read**: [Exercises/README.md](Exercises/README.md)

### **Tests Project**
Comprehensive validation using Google Test framework:

| Component | Tests | Coverage |
|-----------|-------|----------|
| **Image Pipeline** | Single filters, composition, parallelization, memory safety | Correctness, concurrency, edge cases, visual output |
| **Job System** | Job execution, scheduling, work-stealing, dependencies | Functional correctness, thread safety, exception handling |
| **Overall** | 40+ test cases | Thread safety, memory leaks, determinism, performance validation |

➡️ **Read**: [Tests/README.md](Tests/README.md)

### **Benchmarks Project**
Performance profiling using Google Benchmark framework:

| Benchmark | Measurements | Insights |
|-----------|--------------|----------|
| **Filter Performance** | Serial vs parallel, scalar vs SIMD, throughput | Speedup, efficiency, scalability |
| **Pipeline Scaling** | Variable image sizes, thread counts | Cache behavior, synchronization overhead |
| **Thread Pool Overhead** | Task enqueue, execution latency, allocation | Scheduling efficiency, memory overhead |

➡️ **Read**: [Benchmarks/README.md](Benchmarks/README.md)

---

## 🎯 Modern C++ Features Covered

### Core Language Features (C++17/20)

| Feature | Exercises | Purpose |
|---------|-----------|---------|
| **Structured Bindings** | Ex01, Ex02 | Convenient tuple unpacking |
| **Template Metaprogramming** | Ex01 | Compile-time buffer generation |
| **Concepts** | Ex01, Ex02 | Type-safe constraint validation |
| **Variadic Templates** | Ex01, Ex02 | Flexible argument handling |
| **CRTP** | Ex01 | Static polymorphism for filters |
| **Perfect Forwarding** | Ex01, Ex02 | Zero-copy parameter passing |
| **Move Semantics** | All | Efficient ownership transfer |
| **constexpr** | Ex01, Ex02 | Compile-time computation |

### Concurrency Features (C++11/17/20)

| Feature | Exercise | Purpose |
|---------|----------|---------|
| **std::thread** | Ex01 | Basic thread creation |
| **std::jthread** | Ex01, Ex02 | RAII thread management |
| **std::stop_token** | Ex01, Ex02 | Cooperative cancellation |
| **std::stop_source** | Ex01, Ex02 | Cancellation signaling |
| **std::mutex** | Ex01, Ex02 | Mutual exclusion |
| **std::lock_guard** | All | RAII-based locking |
| **std::scoped_lock** | All | Multi-lock RAII |
| **std::unique_lock** | Ex01 | Flexible locking semantics |
| **std::condition_variable** | Ex01 | Thread synchronization |
| **std::barrier** | Ex01 | Phase synchronization |
| **std::atomic** | Ex02 | Lock-free operations |
| **std::future** | Ex01 | Asynchronous results |
| **std::promise** | Ex01 | Result/exception propagation |
| **std::packaged_task** | Ex01 | Task wrapping with futures |

### Standard Library Features

| Feature | Exercise | Purpose |
|---------|----------|---------|
| **std::function** | All | Type-erased callables |
| **std::move_only_function** | Ex01, Ex02 | Non-copyable callables |
| **std::bind_front** | Ex02 | Argument binding |
| **std::invoke** | Ex02 | Generic function calls |
| **std::tuple** | Ex01 | Heterogeneous collections |
| **std::vector** | All | Dynamic arrays |
| **std::queue** | Ex01, Ex02 | FIFO buffers |
| **std::shared_ptr** | Ex01 | Shared ownership |
| **std::unique_ptr** | All | Exclusive ownership |
| **std::string_view** | SimpleLogger | Non-owning string references |
| **std::span** | Ex01 | Contiguous sequence view |
| **std::mdspan** | Ex01 | Multidimensional array view |

### Advanced Patterns

- **RAII (Resource Acquisition Is Initialization)**: All exercises
- **CRTP (Curiously Recurring Template Pattern)**: Ex01 filters
- **Work-Stealing Queue**: Ex02 scheduler
- **Type-Safe Pipeline Composition**: Ex01 with concepts

---

## 📄 License

This project is provided as-is for educational purposes.

---

## ✨ Key Highlights

✅ **Complete End-to-End Examples**: From concept to testing to benchmarking

✅ **Modern C++ Best Practices**: C++20 features with production-quality code

✅ **Real-World Scenarios**: Image processing and job scheduling aren't toy examples

✅ **Comprehensive Testing**: 40+ tests covering correctness, concurrency, and edge cases

✅ **Performance Profiling**: Built-in benchmarks for optimization analysis

✅ **Extensible Design**: Easy to add new filters, schedulers, or exercises

✅ **Well-Documented**: Code comments, inline documentation, README guides

✅ **Visual Studio Integration**: Native IDE support without external tools

---

## 🎓 Learning Outcomes

After completing ModernCpp_Mastery, you will understand:

1. ✅ How to design type-safe abstractions with C++20 concepts
2. ✅ Modern concurrency patterns: thread pools, work-stealing, job systems
3. ✅ RAII principles and resource management
4. ✅ Move semantics and perfect forwarding
5. ✅ Template metaprogramming techniques
6. ✅ How to write testable, performant code
7. ✅ Performance profiling and optimization strategies
8. ✅ Thread safety and synchronization primitives

---
