# 12_ParallelSTL

This project demonstrates C++17 parallel algorithms (Parallel STL) and practical considerations when applying execution policies for CPU‑bound and data‑parallel workloads. Examples include parallel and sequential variants of `std::sort`, `std::for_each`, and `std::transform`, plus simple benchmarking utilities to compare execution policies.

Overview
- Purpose and common scenarios
  - Show how to exploit data parallelism using the C++17 execution policies (`std::execution::par`, `std::execution::seq`, `std::execution::par_unseq`) to accelerate CPU‑intensive and embarrassingly parallel operations.
  - Provide example baselines (sequential) and parallel implementations to compare correctness and performance on large data sets.
  - Demonstrate measurement patterns for micro‑benchmarks and highlight caveats when interpreting timing results.

- Key concepts demonstrated
  - Execution policies: differences between `sequenced`, `parallel`, and `parallel_unsequenced` policies and their intended usage.
  - Determinism and correctness: verifying that parallel algorithms produce the same results as sequential counterparts (sorting, transforms).
  - Side effects and thread safety: ensuring element operations are independent and thread‑safe when using parallel policies (avoid shared mutable state or use synchronization).
  - Workload suitability: parallel algorithms benefit primarily CPU‑heavy, data‑parallel tasks; lightweight or I/O‑bound tasks may not see gains and can incur overhead.
  - Performance measurement: use of high‑resolution clocks and repeated runs to reduce variance, and awareness that results depend on hardware, runtime, and library implementation.

Files
- `ParallelSTL_Basic.h` / `ParallelSTL_Basic.cpp`
  - `generateLargeVector(size_t)`: helper to create large test vectors.
  - `sortParallel` / `sortSequential`: parallel vs sequential sort with timing.
  - `processInParallel` / `processSequentially`: parallel and sequential `for_each` using a CPU‑intensive `complex_calc`.
- `ParallelSTL_Advance.h`
  - `ParallelSTL_Advance` class with `benchmarkTransform` and `benchmarkForEach` overloads for different execution policies and heavier compute kernels to illustrate measurable speedups.
  - `complexCalculation(double)` example of a heavier per‑element computation.
- `12_ParallelSTLTest/ParallelSTLTest.cpp`
  - Unit tests that check correctness (sorted results equality, element-wise equivalence) and print basic performance metrics for informative comparison.

Requirements
- Windows 10/11 (examples target MSVC) or other platforms with a C++17 standard library that supports parallel algorithms.
- Visual Studio 2022
- Compiler and standard library configured for C++17 (ISO C++17)
- Note: Parallel algorithm performance and availability depend on the standard library implementation and the runtime environment (hardware threads, scheduler). Ensure your toolchain's STL implements Parallel STL for the platforms you intend to run.

Build
1. Open the solution in Visual Studio 2022.  
2. Ensure projects use ISO C++17: Project Properties → `C/C++` → `Language` → `C++ Language Standard` → `ISO C++17`.  
3. Build the solution (Right‑click solution → `Build Solution`).

Notes and best practices
- Ensure that operations applied by parallel algorithms are free of data races and do not rely on shared mutable state unless properly synchronized.
- Use `std::execution::par_unseq` only when operations are safe to vectorize and reorder.
- Interpret micro‑benchmark results cautiously: warm‑up runs, CPU frequency scaling, and other system load affect timings.
- Prefer algorithmic changes (reducing complexity) before parallelizing; parallelism is not a substitute for inefficient algorithms.
- Add license information as needed (e.g., MIT).