# 12_ParallelSTLTest

This test project contains validation and basic performance comparisons for the `12_ParallelSTL` examples. Tests verify correctness of parallel algorithms compared to sequential implementations and provide informative timing output for side‑by‑side comparison.

Contents
- `ParallelSTLTest.cpp`
  - `SortPerformance_And_Correctness`: generates a large vector, runs sequential and parallel sorts, verifies both are sorted and identical, and prints timing measurements.
  - `ForEach_ParallelExecutionIsCorrect`: exercises sequential and parallel `for_each` using a CPU‑intensive function and asserts element-wise equivalence.

Requirements
- Visual Studio 2022
- MSVC with C++17 support (ISO C++17)
- Google Test configured if running unit tests as part of the solution

Build & Run Tests
- Build the solution in Visual Studio (Right‑click solution → `Build Solution`).  
- Run tests from Test Explorer (Test → Test Explorer) or execute the produced test executable:
  Example: `.\12_ParallelSTLTest\Debug\12_ParallelSTLTest.exe`

Test guidance
- Tests include a large test vector (1,000,000 elements) to make parallel speedups observable on multi‑core systems; adjust `TEST_VECTOR_SIZE` in `ParallelSTLTest.cpp` if your environment has limited memory or CPU resources.
- Expect timing variability across runs and environments. Use multiple runs to get stable measurements.
- If tests fail or parallel algorithms are not available, confirm your standard library supports Parallel STL on the target platform and that the project is compiled with ISO C++17.

Notes
- The test harness focuses on correctness first; performance checks are informative but not strict guarantees.
- When reporting issues, include test output, platform details, and compiler/standard‑library versions for faster diagnosis.