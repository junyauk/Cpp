# 10_NonTypeTemplateTest

Unit tests for the `10_NonTypeTemplate` examples (Google Test). The tests validate compile-time computations exposed via NTTPs, correct interaction between compile-time and runtime hash functions, NTTP-driven type deductions, and behavior of NTTP-based utility types.

Contents
- `NonTypeTemplate_AdvanceTest.cpp`
  - `ConstexprHash_DifferentKeys` / `ConstexprHash_SameKeys`: verify compile-time FNV‑1a hash values for different and identical string keys and ensure runtime/hash consistency.
  - `SizedArray_TypeDeduction`: validate `createSizeArray<N>()` produces `std::array<int, N>` (with `static_assert` verification).
  - `Range_Int` / `Range_Char`: validate `Range<S,E>` size calculation and `getInfo()` contents for both integer and character NTTPs; `static_assert` checks ensure `ValueType` is deduced correctly.

Requirements
- Visual Studio 2022
- MSVC configured for ISO C++17
- Google Test (gtest) available and configured in the solution

Build & Run Tests
- Build the solution in Visual Studio (Right‑click solution → `Build Solution`).  
- Run tests from Test Explorer (Test → Test Explorer) or execute the produced test binary:
  Example: `.\10_NonTypeTemplateTest\Debug\10_NonTypeTemplateTest.exe`

Notes
- Tests intentionally define string NTTP sources with suitable linkage to comply with C++17 rules for pointer NTTPs.
- If tests fail, verify that all headers are included and that compilation uses ISO C++17.
- Report failing tests with the exact test output and the compiler/VS configuration for faster diagnosis.