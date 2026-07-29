# 09_TemplateDeductionTest

Unit tests for CTAD examples (Google Test). Tests verify that template argument deduction and user-defined deduction guides behave as intended in the `09_TemplateDeduction` examples.

Contents
- `TemplateDeductionTest.cpp`
  - `SimpleIntWrapper_DeducesCorrectly`: verifies implicit CTAD for `SimpleWrapper<int>`.
  - `SimpleStringWrapper_DeducesCorrectly`: verifies implicit CTAD for `SimpleWrapper<std::string>`.
  - `CountedBuffer_DeductionGuideUsed`: verifies deduction guide for `CountedBuffer` and confirms `getCount()` result.

Requirements
- Visual Studio 2022
- MSVC with C++17 support (ISO C++17)
- Google Test configured in the solution

Build & Run Tests
- Build the solution in Visual Studio (Right‑click solution → `Build Solution`).
- Run tests from Test Explorer (Test → Test Explorer) or run the produced test executable:
  Example: `.\09_TemplateDeductionTest\Debug\09_TemplateDeductionTest.exe`

Notes
- Some CTAD behaviors can be validated at compile time using `static_assert` on deduced types; tests here validate observable runtime results.
- If tests fail, verify that projects compile with ISO C++17 and that deduction guides are visible to the translation unit (headers included).