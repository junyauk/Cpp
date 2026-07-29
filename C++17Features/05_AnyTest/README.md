# 05_AnyTest

Test project for `05_Any` providing Google Test unit tests that verify `std::any` usage patterns and semantics used in the implementation.

Contents
- `AnyTest.cpp` — Tests include:
  - Safe access tests using `getConfigValueSafe<T>` (type match, mismatch, missing key).
  - Unsafe access tests for `getStringConfigValueUnsafe` (success and `std::bad_any_cast` on mismatch).
  - Type inspection tests for `getConfigType`.

Requirements
- Visual Studio 2022
- Google Test configured in the solution (vcpkg, submodule, or vendor)
- MSVC with C++17 support

Build & Run Tests
- Build the solution in Visual Studio (Right-click solution → Build Solution).  
- Run tests from Test Explorer (Test → Test Explorer) or execute the test binary:
  Example: `.\05_AnyTest\Debug\05_AnyTest.exe`

Expected behaviors
- Safe retrieval returns an engaged `std::optional` only when the stored type matches the requested type.
- Unsafe retrieval throws `std::bad_any_cast` on type mismatch.
- `getConfigType` returns a readable type name for known types and `"empty"` for missing keys.

Notes
- If tests fail, verify Google Test configuration and that projects compile with ISO C++17.
