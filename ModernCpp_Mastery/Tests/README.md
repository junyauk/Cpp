# Tests - ModernCpp_Mastery

Comprehensive test suite for the ModernCpp_Mastery exercises using **Google Test (gtest)** framework. This project validates the correctness and performance characteristics of each exercise implementation.

---

## Overview

The Tests project contains unit tests and integration tests organized by exercise. Each test suite validates:
- **Functional correctness**: Algorithms produce expected results
- **Thread safety**: Concurrent operations don't cause data races or deadlocks
- **Memory safety**: No memory leaks, buffer overflows, or use-after-free
- **Edge cases**: Boundary conditions and error handling
- **Performance characteristics**: Execution meets reasonable performance baselines

### Test Framework
- **Framework**: Google Test (gtest/googletest)
- **Integration**: Visual Studio Test Explorer
- **Standard**: C++20 or later

---

## Test Structure

```
Tests/
├── Ex01_ImagePipeline/
│   └── image_pipeline_tests.cpp
├── Ex02_JobSystem/
│   └── job_tests.cpp
└── packages.config
```

---

## Exercise 01: Image Pipeline Tests (`image_pipeline_tests.cpp`)

### Test Objectives
Verify that the image processing pipeline correctly:
- Chains multiple filters together
- Applies filters to entire images and image slices
- Handles different pixel types and filter strategies
- Parallelizes work across threads without synchronization issues
- Produces deterministic results across multiple runs

### Test Categories

#### 1. **Single Filter Tests**
Test individual filter implementations in isolation:
- **Grayscale Conversion**: Validates RGB→Gray color space conversion
- **Sepia Tone**: Verifies sepia tone application with correct color coefficients
- **Blur**: Checks kernel-based convolution produces smooth output
- **Edge Detection**: Validates edge detection algorithms
- **Threshold**: Verifies binary thresholding at specified levels

**Key Validations:**
- Pixel values fall within expected ranges
- Filter output dimensions match input
- Boundary pixel handling (edges) doesn't cause artifacts
- Results are bit-identical across multiple invocations (determinism)

#### 2. **Pipeline Composition Tests**
Test filter chaining and type safety:
- **Two-Filter Pipeline**: Grayscale → Sepia
- **Three-Filter Pipeline**: Grayscale → Blur → Threshold
- **Filter Compatibility**: Ensure compile-time validation prevents incompatible chains

**Key Validations:**
- Intermediate buffers are correctly sized
- Filters apply in correct order
- Output matches expected composition result
- No intermediate memory is leaked

#### 3. **Parallel Execution Tests**
Test thread pool and work distribution:
- **Single-Threaded Pipeline**: Baseline performance
- **Multi-Threaded Pipeline**: Verifies work is distributed correctly
- **Slice Consistency**: Each slice produces identical results to full-image processing
- **Barrier Synchronization**: Ensures filters wait for all slices before advancing stages

**Key Validations:**
- Parallel results match serial baseline (determinism)
- No data races or race conditions
- Thread pool properly manages worker threads
- Barrier prevents premature stage transitions

#### 4. **Memory and Resource Tests**
Validate resource management:
- **ThreadPool Lifecycle**: Threads are created and destroyed cleanly
- **Image Memory**: No buffer overflows or memory leaks
- **Stop Token**: Thread cancellation works correctly
- **Exception Safety**: Proper cleanup even if filters throw

**Key Validations:**
- No double-delete or use-after-free errors
- Thread local storage is cleaned up
- Condition variables are destroyed safely
- RAII principles are upheld

#### 5. **Edge Case Tests**
Stress testing and boundary conditions:
- **Empty Images**: 0×0 pixel images don't crash
- **1×1 Images**: Single-pixel images process correctly
- **Large Images**: 4K and 8K resolutions process without issues
- **Extreme Pixel Values**: Min/max pixel values don't overflow calculations
- **Mismatched Dimensions**: Source and destination size mismatches are caught

**Key Validations:**
- Proper error handling and exceptions thrown
- No undefined behavior
- Memory allocation/deallocation is balanced

#### 6. **Visual/Output Tests**
Generate and compare output images:
- **PPM File Export**: Saves processed images as PPM for visual inspection
- **Reference Comparison**: Compares output against golden reference images
- **Pixel-Perfect Validation**: Bitwise comparison of pixel values

**Key Validations:**
- File I/O succeeds without corruption
- Output images can be opened in image viewers
- Color values and gradients are preserved
- No loss of information during processing

### Modern C++ Features Tested

| Feature | Test Coverage |
|---------|---------------|
| **C++20 Concepts** | Pipeline type validation, incompatible filter rejection |
| **Template Metaprogramming** | Intermediate buffer generation, type inference |
| **std::jthread** | Automatic thread cleanup, RAII semantics |
| **std::stop_token** | Thread cancellation during pipeline destruction |
| **std::barrier** | Multi-threaded synchronization across filter stages |
| **std::condition_variable_any** | Worker thread wake-up and notification |
| **std::move_only_function** | Task queue storage and execution |
| **Perfect Forwarding** | Parameter passing through pipeline stages |
| **std::future / std::promise** | Asynchronous task result retrieval |
| **Memory Safety** | No memory leaks, buffer safety, pointer validity |
| **Thread Safety** | No data races, atomic operations correct |

---

## Exercise 02: Job System Tests (`job_tests.cpp`)

### Test Objectives
Verify that the job scheduling system:
- Correctly enqueues and executes jobs with parameters
- Distributes work fairly across worker threads
- Handles job dependencies and completion tracking
- Provides deterministic scheduling and execution
- Manages thread lifecycle properly

### Test Categories

#### 1. **Basic Job Execution Tests**
Test core job functionality:
- **Simple Job**: Execute a job with no parameters
- **Parameterized Job**: Execute a job with multiple arguments
- **Callable Verification**: Job captures and invokes lambdas correctly
- **Return Value Handling**: Job completion status is tracked

**Key Validations:**
- Job executes exactly once
- Parameters are passed correctly
- Job result is available after execution
- No premature job execution

#### 2. **Job Scheduler Tests**
Test job queue management:
- **Enqueue Single Job**: Add one job to scheduler
- **Enqueue Multiple Jobs**: Add many jobs in sequence
- **Dequeue and Execute**: Jobs execute in FIFO or priority order
- **Scheduler State**: Tracks pending, running, and completed jobs

**Key Validations:**
- Jobs are stored and retrieved correctly
- Job order is preserved (or priority ordering respected)
- Scheduler state remains consistent
- No jobs are lost or duplicated

#### 3. **Work Stealing Tests**
Test load balancing:
- **Steal from Peer Queue**: Worker steals job from another worker's queue
- **Balanced Distribution**: Work is evenly distributed across threads
- **No Stealing from Empty Queue**: Stealing gracefully handles empty queues
- **Thread Affinity**: Workers prefer their own queue before stealing

**Key Validations:**
- Stealing doesn't introduce data races
- All jobs eventually execute
- Load is balanced across threads
- Performance improves with work stealing

#### 4. **Job Dependencies Tests**
Test dependency tracking:
- **Simple Dependency**: Job B waits for Job A completion
- **Dependency Chain**: Job C waits for B, which waits for A
- **Parallel with Dependencies**: Multiple independent jobs run while one waits
- **Circular Dependency Detection**: System detects and rejects cycles

**Key Validations:**
- Dependencies are respected (correct execution order)
- Dependent job doesn't execute until dependency completes
- No deadlock on circular dependencies
- Performance isn't degraded unnecessarily

#### 5. **Thread Management Tests**
Validate worker thread lifecycle:
- **Thread Creation**: Correct number of worker threads spawned
- **Thread Shutdown**: Graceful shutdown without hanging
- **Thread Cancellation**: Stop tokens signal threads to exit
- **Resource Cleanup**: Thread-local storage cleaned up properly

**Key Validations:**
- No thread leaks
- Shutdown completes in reasonable time
- All threads terminate cleanly
- No resource exhaustion

#### 6. **Stress and Concurrent Tests**
High-load testing:
- **High Job Volume**: Schedule thousands of jobs
- **Concurrent Execution**: Many jobs executing simultaneously
- **Rapid Enqueue/Dequeue**: Stress-test queue under high contention
- **Variable Job Duration**: Mix of fast and slow jobs

**Key Validations:**
- No crashes or undefined behavior
- Performance scales reasonably
- No memory leaks under sustained load
- Scheduling remains fair

#### 7. **Exception Handling Tests**
Test robustness:
- **Job Throws Exception**: Exception is caught and logged, doesn't crash scheduler
- **Scheduler State After Exception**: Scheduler continues operating
- **Error Reporting**: Exception details are available to caller
- **No Cascading Failures**: One job's failure doesn't prevent others

**Key Validations:**
- Exceptions don't terminate worker threads
- Scheduler state remains valid
- Error information is preserved
- Other jobs continue executing

### Modern C++ Features Tested

| Feature | Test Coverage |
|---------|---------------|
| **C++20 Concepts** | JobCallable validation, signature correctness |
| **std::bind_front** | Argument binding without type erasure |
| **std::move_only_function** | Non-copyable callable storage |
| **std::jthread** | Worker thread management and cancellation |
| **std::stop_token** | Cooperative shutdown signaling |
| **Perfect Forwarding** | Argument passing through schedulers |
| **Variadic Templates** | Flexible job argument handling |
| **std::invoke / std::invoke_result_t** | Generic function invocation |
| **std::atomic** | Lock-free shared state updates |
| **Thread Safety** | No data races in concurrent scheduling |
| **Exception Safety** | RAII and exception guarantees |

---

## Best Practices

### Writing New Tests

1. **Use Descriptive Names**: Test name should describe what is being tested
   ```cpp
   TEST(ImagePipelineTests, GrayscaleFilter_ProducesCorrectPixelValues)
   ```

2. **Follow Arrange-Act-Assert Pattern**:
   ```cpp
   TEST(Ex, Case) {
	   // Arrange: Set up test data
	   Image<RgbaPixel> src(100, 100);
	   Image<GrayPixel> dst(100, 100);

	   // Act: Perform the operation
	   pipeline.apply(src, dst);

	   // Assert: Verify the result
	   ASSERT_EQ(dst.pixel(0, 0).value, expectedValue);
   }
   ```

3. **Use Fixtures for Shared Setup**:
   ```cpp
   class ImagePipelineTests : public ::testing::Test {
   protected:
	   Image<RgbaPixel> testImage{256, 256};
	   // Common setup/teardown
   };
   ```

4. **Test Edge Cases**: Empty inputs, single-pixel images, max values

5. **Avoid Test Interdependencies**: Each test should be independent and runnable in any order

---

## Dependencies

- **Google Test (gtest)**: Unit testing framework
  - Included via NuGet package: `googletest`
  - Version: Compatible with C++20

### Visual Studio Integration
- **Google Test Adapter**: Test Explorer integration
  - Can be installed from Visual Studio Marketplace
  - Enables running/debugging tests from IDE

---

## Performance Benchmarks

Expected performance characteristics:

| Test | Single-Threaded | Multi-Threaded | Speedup |
|------|-----------------|----------------|---------|
| 1024×1024 Image | ~50ms | ~15ms | ~3.3× |
| 100 Jobs | ~100µs | ~30µs | ~3.3× |
| 1000 Jobs | ~1ms | ~0.4ms | ~2.5× |

*Values are approximate and vary by hardware*


