# 04_VariantTest

Test project for `04_Variant` containing unit tests that verify `std::variant` behaviors shown in the implementation.

Contents
- `VariantTest.cpp` / `Variant_AdvanceTest.cpp` — Google Test cases covering:
  - Basic variant storage, type checks, `std::get` behavior.
  - `processAllValues()` effects (int/double doubled, strings appended).
  - `convertValueToString()` correctness across held types.
  - Advanced `processMultipleVariants()` combinations.
  - `calculateValue()` success/error branches and `checkResultForError()` output.
  - `checkStatus()` handling of `std::monostate`, `int`, and `bool`.

Requirements
- Visual Studio 2022
- Google Test configured in the solution (vcpkg, submodule, or vendor)
- MSVC with C++17 support

Build & Run Tests
- Build the solution in Visual Studio (Right-click solution → Build Solution).
- Run tests from Test Explorer (Test → Test Explorer) or execute the test binary (e.g., `.\04_VariantTest\Debug\04_VariantTest.exe`).

Notes
- If tests fail, verify Google Test configuration and that all projects target ISO C++17.
- When adding more variant alternatives, update visitors and `convertValueToString` to handle new types.
