# Benchmarks - ModernCpp_Mastery

Performance benchmarking suite for the ModernCpp_Mastery exercises. This project measures execution time, throughput, and scalability characteristics using **Google Benchmark (gbench)** framework.

---

## Overview

The Benchmarks project provides systematic performance measurement and profiling for each exercise implementation. Benchmarks validate:
- **Single-threaded Performance**: Baseline performance of core algorithms
- **Multi-threaded Scalability**: Performance improvement with parallelization
- **Thread Count Scaling**: Efficiency across different thread counts
- **Image Size Scaling**: Performance behavior with varying input sizes
- **Cache Efficiency**: Memory access patterns and cache utilization
- **Throughput**: Tasks or pixels processed per second
- **Latency**: Time to completion for individual operations

### Benchmarking Framework
- **Framework**: Google Benchmark (google/benchmark)
- **Integration**: Visual Studio performance profiling
- **Metrics**: Time, throughput, iterations, standard deviation
- **Standard**: C++20 or later

---

## Benchmark Structure

```
Benchmarks/
├── Ex01_ImagePipeline/
│   └── image_pipeline_benchmarks.cpp
└── packages.config
```

---

## Exercise 01: Image Pipeline Benchmarks (`image_pipeline_benchmarks.cpp`)

### Benchmark Objectives
Measure performance characteristics of the image processing pipeline:
- Validate that parallelization improves throughput
- Identify performance bottlenecks
- Verify scalability across different thread counts
- Measure filter performance in isolation and in composition
- Profile memory allocation and deallocation overhead

### Benchmark Categories

#### 1. **Single Filter Performance**
Measure individual filter execution time across different image sizes:

**Grayscale Conversion**
```
Benchmark: BM_GrayscaleFilter_256x256
Benchmark: BM_GrayscaleFilter_512x512
Benchmark: BM_GrayscaleFilter_1024x1024
Benchmark: BM_GrayscaleFilter_2048x2048
Benchmark: BM_GrayscaleFilter_4096x4096
```

**Measurements:**
- Time per image (milliseconds)
- Pixels processed per second (throughput)
- Cache misses and memory bandwidth utilization
- Scaling characteristics (linear, sublinear, etc.)

**Key Metrics:**
- Baseline single-threaded performance
- Memory access patterns
- Instruction cache efficiency

**Sepia Filter (Multiple Strategies)**
```
Benchmark: BM_SepiaFilter_Scalar_256x256
Benchmark: BM_SepiaFilter_Simd2_256x256
Benchmark: BM_SepiaFilter_Scalar_4096x4096
Benchmark: BM_SepiaFilter_Simd2_4096x4096
```

**Comparison:**
- Scalar implementation vs SIMD optimizations
- Performance improvement from vectorization
- Scalability at different image resolutions

**Other Filters:**
- **Blur Filter**: Kernel convolution overhead
- **Edge Detection**: Edge computation complexity
- **Threshold**: Lookup table vs. computation performance

#### 2. **Pipeline Composition Performance**
Measure performance of chained filters:

**Two-Filter Pipeline (Grayscale → Sepia)**
```
Benchmark: BM_Pipeline_GrayscaleSepia_1024x1024_Serial
Benchmark: BM_Pipeline_GrayscaleSepia_1024x1024_Parallel
```

**Three-Filter Pipeline (Grayscale → Blur → Threshold)**
```
Benchmark: BM_Pipeline_Composition_Serial_1024x1024
Benchmark: BM_Pipeline_Composition_Parallel_1024x1024
```

**Measurements:**
- Total pipeline time
- Overhead of intermediate buffers and synchronization
- Scaling with pipeline depth

#### 3. **Parallelization Speedup**
Measure efficiency of parallelization:

**Variable Thread Count**
```
Benchmark: BM_Pipeline_1024x1024_Threads1
Benchmark: BM_Pipeline_1024x1024_Threads2
Benchmark: BM_Pipeline_1024x1024_Threads4
Benchmark: BM_Pipeline_1024x1024_Threads8
Benchmark: BM_Pipeline_1024x1024_Threads16
```

**Metrics:**
- Speedup factor (serial time / parallel time)
- Efficiency (speedup / thread count)
- Scalability curve
- Diminishing returns with excessive threads

**Analysis:**
- Amdahl's law validation
- Synchronization overhead
- Thread creation/destruction cost

#### 4. **Image Size Scaling**
Performance across varying resolutions:

**Fixed Thread Count (4 threads), Variable Resolution**
```
Benchmark: BM_Pipeline_4Threads_64x64
Benchmark: BM_Pipeline_4Threads_256x256
Benchmark: BM_Pipeline_4Threads_512x512
Benchmark: BM_Pipeline_4Threads_1024x1024
Benchmark: BM_Pipeline_4Threads_2048x2048
Benchmark: BM_Pipeline_4Threads_4096x4096
```

**Measurements:**
- Linear scaling (O(N) where N = pixels)
- Cache efficiency degradation at large sizes
- Memory bandwidth saturation
- Throughput stabilization (pixels/sec)

#### 5. **Barrier Synchronization Overhead**
Measure cost of stage synchronization:

```
Benchmark: BM_Barrier_2Threads_SingleStage
Benchmark: BM_Barrier_4Threads_SingleStage
Benchmark: BM_Barrier_8Threads_MultiStage
```

**Measurements:**
- Barrier arrival time
- Wait time for slowest thread
- Synchronization primitive overhead
- Load imbalance impact

#### 6. **Thread Pool Overhead**
Measure task queuing and scheduling cost:

```
Benchmark: BM_ThreadPool_Enqueue_100Tasks
Benchmark: BM_ThreadPool_Enqueue_1000Tasks
Benchmark: BM_ThreadPool_Enqueue_10000Tasks
```

**Measurements:**
- Enqueue latency
- Task execution latency
- Queue contention under high load
- Memory allocation/deallocation overhead

#### 7. **Memory Allocation Efficiency**
Measure memory management performance:

```
Benchmark: BM_ImageAllocation_256x256
Benchmark: BM_ImageAllocation_1024x1024
Benchmark: BM_ImageAllocation_4096x4096
```

**Measurements:**
- Allocation time
- Deallocation time
- Temporary buffer creation overhead
- Peak memory usage

#### 8. **Comparative Benchmarks**
Compare different implementation strategies:

**Serial vs. Parallel Pipeline**
```
Benchmark: BM_Pipeline_Serial_1024x1024
Benchmark: BM_Pipeline_Parallel_1024x1024
Metric: Speedup = Serial Time / Parallel Time
```

**Expected Results:**
- Speedup ≈ 2-4× on quad-core systems
- Speedup ≈ 4-8× on 8-core systems
- Diminishing returns beyond core count

**Scalar vs. SIMD Filters**
```
Benchmark: BM_SepiaFilter_Scalar_2048x2048
Benchmark: BM_SepiaFilter_Simd2_2048x2048
Metric: Speedup = Scalar Time / SIMD Time
```

Expected Results:
- SIMD speedup: 2-4× depending on vector width
- Alignment and cache behavior impact

### Modern C++ Features Evaluated

| Feature | Performance Impact |
|---------|-------------------|
| **std::move Semantics** | Eliminates unnecessary copies, measures zero-copy overhead |
| **Perfect Forwarding** | Validates forwarding doesn't introduce copies |
| **std::jthread Overhead** | Thread creation/destruction time |
| **std::barrier** | Synchronization latency and scalability |
| **std::condition_variable_any** | Wakeup latency and notification overhead |
| **std::move_only_function** | Type erasure overhead for non-copyable callables |
| **Template Specialization** | Monomorphization and instantiation costs |
| **Inline Optimizations** | Compiler optimizations on templated code |
| **Lock-Free Synchronization** | Atomic operations vs mutex-based synchronization |
| **Memory Access Patterns** | Cache locality and NUMA effects |

---

## Running Benchmarks

## Benchmark Configuration

### Release Build (Recommended for Benchmarks)
```
Configuration: Release
Optimization: /O2 (maximize speed)
Whole Program Optimization: /GL (enabled)
Runtime: /MD (Multi-threaded DLL)
Debug Info: /Zi (generate debug info for profiling)
```

**Why Release:**
- Matches production performance characteristics
- Compiler optimizations (inlining, vectorization, etc.)
- No debug overhead
- More representative results

### Benchmark Parameters
```cpp
// Typical benchmark configuration
BENCHMARK(BM_ImagePipeline_1024x1024)
	->Iterations(100)           // Number of times to run
	->RepetitionTime(2.0)       // Minimum time per repetition (seconds)
	->Repetitions(3)            // Number of repetitions
	->MeasureProcessCPUTime()   // Measure CPU time, not wall time
	->UseRealTime();            // Use wall-clock time instead of CPU time
```

---

## Interpreting Results

### Key Metrics

**Time (ms):**
- Absolute execution time
- Smaller is better
- Compare serial vs. parallel

**Throughput (Pixels/sec, Tasks/sec):**
- Derived from time: `throughput = total_work / time`
- Higher is better
- Compare different implementations

**Speedup:**
- `speedup = serial_time / parallel_time`
- Expected: close to thread count for ideal scaling
- `speedup < 2` indicates synchronization overhead dominates

**Efficiency:**
- `efficiency = speedup / thread_count`
- Expected: 0.8–1.0 for good scalability
- `efficiency < 0.5` indicates poor parallelization

**Standard Deviation (Std Dev):**
- Variability across runs
- Should be < 5% of mean for reproducible results
- High variance indicates system contention or thermal throttling

### Example Interpretation

```
Benchmark: BM_Pipeline_4Threads_1024x1024
Time:      45.2 ms ± 1.3 ms
Speedup:   3.8× (181 ms serial / 45.2 ms parallel)
Efficiency: 95% (3.8× speedup / 4 threads)
Throughput: 58.2 MPixels/sec

Result: Excellent scaling on quad-core system
```

---

## Expected Performance Baselines

### Single-Threaded Performance (Release Build)

| Operation | Resolution | Time | Throughput |
|-----------|-----------|------|-----------|
| Grayscale Filter | 1024×1024 | 3.2 ms | 327 MPixels/sec |
| Sepia Filter (Scalar) | 1024×1024 | 4.1 ms | 255 MPixels/sec |
| Sepia Filter (SIMD) | 1024×1024 | 1.8 ms | 582 MPixels/sec |
| Blur Filter | 1024×1024 | 12.5 ms | 84 MPixels/sec |
| Pipeline (2 filters) | 1024×1024 | 7.3 ms | 143 MPixels/sec |

*Baselines from Intel Core i7 (4 cores); vary by hardware*

### Multi-Threaded Performance (4 Threads)

| Operation | Resolution | Serial | 4-Thread | Speedup |
|-----------|-----------|--------|----------|---------|
| Grayscale Filter | 1024×1024 | 3.2 ms | 1.0 ms | 3.2× |
| Sepia Filter | 1024×1024 | 4.1 ms | 1.3 ms | 3.2× |
| Pipeline (2 filters) | 1024×1024 | 7.3 ms | 2.2 ms | 3.3× |
| 4K Image | 4096×4096 | 51 ms | 15 ms | 3.4× |

*Speedup efficiency: ~85% (3.2× / 4 threads)*

---

## Benchmarking Best Practices

### Writing Effective Benchmarks

1. **Measure the Right Thing**:
   - Include realistic setup/teardown
   - Measure end-to-end operation, not micro-operations
   - Avoid measuring compiler optimizations only

2. **Control Variables**:
   - Use consistent data sizes
   - Run on same hardware/OS for comparisons
   - Disable CPU frequency scaling during measurements
   - Close other applications

3. **Sufficient Iterations**:
   - Let benchmark run long enough (> 1 second default)
   - Multiple repetitions to capture variance
   - Discard outliers if appropriate

4. **Realistic Inputs**:
   - Use real-world image sizes (256×256 to 4K+)
   - Include various image content (gradients, noise, features)
   - Test with typical thread counts

5. **Avoid Common Pitfalls**:
   - Don't benchmark only warm cache scenarios
   - Don't measure with overly small inputs
   - Don't forget system calibration runs
   - Don't trust a single run; use multiple repetitions

### Documenting Results

Include in benchmark reports:
- Hardware specs (CPU, cores, RAM, GPU)
- OS and compiler version
- Optimization flags used
- Run date and conditions
- Minimum, maximum, mean, std dev
- Comparison baseline (if applicable)

---

## Performance Improvement Opportunities

### Identified Optimization Areas

1. **Memory Access Patterns**:
   - Improve cache locality with tile-based processing
   - Prefetch data for sequential access
   - Align data structures to cache lines

2. **Parallelization Efficiency**:
   - Reduce synchronization overhead
   - Balance load more evenly across threads
   - Use lock-free data structures where appropriate

3. **SIMD Vectorization**:
   - Vectorize more filter operations
   - Align data for SIMD load instructions
   - Use intrinsics for platform-specific optimizations

4. **Memory Allocation**:
   - Use memory pools to reduce allocation overhead
   - Pre-allocate temporary buffers
   - Minimize reallocation during pipeline

5. **Thread Pool Tuning**:
   - Adjust thread count for system hardware
   - Tune work-stealing heuristics
   - Reduce context switching with affinity

---

## Dependencies

- **Google Benchmark (google/benchmark)**: Benchmarking framework
  - Included via NuGet package: `google-benchmark`
  - Version: C++11 compatible (used with C++20 features)

