# 07_ConstexprLambdaTest

This test project contains unit tests (Google Test) for the `07_ConstexprLambda` examples. Tests validate both runtime behavior and compile‑time properties (where `static_assert` is used) of constexpr lambda patterns and related utilities.

Contents
- `ConstexprLambdaTest.cpp`
  - Runtime tests for `ConstexprLambda_Basic`:
    - `calculateSquare` runtime correctness.
    - `getCompileTimeArray` values and constexpr usability.
    - `calculateRuntimeSum` correctness.
- `ConstexprLambda_AdvanceTest.cpp`
  - Compile‑time and constexpr checks for `ConstexprLambda_Advance`:
    - `calculateFactorial` / simplified power functions validated in constexpr contexts.
    - IIFE (`inline static constexpr`) initializations such as `Config::MAX_VALUE` and `Config::DATA_PATTERN`.
    - Capture and constexpr capture verification via `calculateOffsetValue`.
  - Uses `static_assert` in some tests to ensure certain values are usable at compile time.

Requirements
- Visual Studio 2022
- MSVC configured for C++17 (ISO C++17)
- Google Test (gtest) available and configured in the solution

Build
1. Open the solution in Visual Studio 2022.  
2. Ensure the test project and the implementation target the ISO C++17 standard:
   Project Properties → `C/C++` → `Language` → `C++ Language Standard` → `ISO C++17`.  
3. Build the solution (Right‑click solution → `Build Solution`).

Run tests
- Use Visual Studio Test Explorer (Test → Test Explorer) to run all or selected tests.
- Or execute the produced test binary directly, e.g.:
  `.\07_ConstexprLambdaTest\Debug\07_ConstexprLambdaTest.exe`

Expected behavior summary
- Runtime assertions for arithmetic and array values pass.
- `getCompileTimeArray` can be used in a `constexpr` context (validated by `static_assert`).
- `Config::MAX_VALUE` and `Config::DATA_PATTERN` are initialized as constexpr values and match expected constants.
- Compile‑time `static_assert` checks included in tests validate compile‑time evaluability where applicable.

Notes
- Some patterns intentionally avoid complex recursive constexpr lambdas for C++17 compatibility; moving to C++20 allows more ergonomic `constexpr` lambdas and recursion.
- If tests fail, verify that the projects compile with ISO C++17 and that Google Test is correctly configured.
- Add license or contributing references in the parent project README if desired.