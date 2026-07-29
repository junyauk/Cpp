# 03_OptionalTest

Test project for `03_Optional` demonstrating unit tests (Google Test) for advanced `std::optional` usages.

Contents
- `Optional_AdvanceTest.cpp` — tests for:
  - `chainedProcessing`: success and failure scenarios for stage1/stage2.
  - `checkMoveCost`: verifies move semantics and that the optional becomes empty after the move.
  - `checkExceptionSafety`: verifies behavior when `value()` is called on engaged vs disengaged optionals.

Requirements
- Visual Studio 2022
- Google Test configured in the solution (vcpkg, submodule, or vendor)
- MSVC with C++17 support

Build & Run Tests
- Build the solution in Visual Studio (Right-click solution → Build Solution).
- Run tests from __Test Explorer__ (Test → Test Explorer) or run the test executable:
  Example: `.\03_OptionalTest\Debug\03_OptionalTest.exe`

Test expectations summary
- Chaining_Success: returns an engaged optional with the expected string when stages succeed.
- Chaining_FailureStage1 / Stage2: returns `std::nullopt` when the corresponding stage fails.
- CheckMoveCost_MoveSemantics: moved `LargeData` name contains `"_M"` and the source optional is empty after move.
- ExceptionSafety_Success / Failure: verifies `value()` success and the catching of `std::bad_optional_access`.

Notes
- If tests fail, verify Google Test include/libs and that projects use ISO C++17.
- Provide test output and build configuration in Issues when reporting failures.
