# 11_InlineVariablesTest

Unit tests (Google Test) validating `11_InlineVariables` examples. Tests ensure `inline` variables behave as a single shared instance across translation units and confirm correct access, initialization, and lifetime semantics.

Contents
- `InlineVariablesTest.cpp`
  - Tests for:
    - `VERSION_STRING` access equality.
    - `CONFIG_DEFAULT` map access and lookup.
    - `Counter::instanceCount` single-instance behavior across TUs (simulated via `access_inline_counter()`).
- The tests reset and inspect `Counter::instanceCount` to validate increments/decrements and ODR compliance.

Requirements
- Visual Studio 2022
- MSVC with C++17 support (ISO C++17)
- Google Test configured in the solution

Build & Run Tests
- Build the solution in Visual Studio (Right‑click solution → `Build Solution`).  
- Run tests from Test Explorer (Test → Test Explorer) or execute the produced test binary:
  Example: `.\11_InlineVariablesTest\Debug\11_InlineVariablesTest.exe`

Notes
- Tests simulate access from multiple translation units to demonstrate that inline variables produce a single shared instance.
- If tests fail, verify that headers are included consistently and that the project is compiled with ISO C++17.