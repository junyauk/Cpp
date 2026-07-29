# 01_StructuredBindingTest

This test project contains Google Test unit tests for the `01_StructuredBinding` examples.

Contents
- `StructuredBinding_BasicTest.cpp` — Tests for:
  - `insertToMap` behavior (insertion success / duplicate key handling)
  - `getLabelFromStruct` structured-binding extraction from `Point`
  - `procssTuple` tuple extraction and string composition
- Test project references the implementation in `../01_StructuredBinding/structured_binding_basic.h` and corresponding `.cpp`.

Prerequisites
- Visual Studio 2022
- Google Test (gtest) available and configured in the solution
- MSVC with C++17 support

Build
1. Open the solution in Visual Studio 2022.
2. Ensure test project references or links Google Test correctly (either via vcpkg, vendor folder, or solution-level test framework project).
3. Build the solution (Right-click solution → Build Solution).

Run tests
- In Visual Studio: Open __Test Explorer__ (Test → Test Explorer) and run all tests or the specific `StructuredBindingTest` fixture.
- Alternatively, run the test executable produced by the test project from the command line:
  - Example path: `.\01_StructuredBindingTest\Debug\01_StructuredBindingTest.exe`
  - Running the executable will execute the Google Test suite and print results to stdout.

Expected tests (summary)
- InsertToMap_NewKey_Success — inserting a new key returns true and map size increases.
- InsertToMap_ExistingKey_Failure — inserting an existing key returns false; original entries remain.
- GetLabelFromStruct_CorrectlyBinds — `getLabelFromStruct` returns the label passed to `Point`.
- ProcessTuple_CorrectlyExtractsAndCombines — `procssTuple` returns the combined "text,number" string.

Notes
- The implementation function is named `procssTuple` (typo) — tests use that name; consider renaming if desired.
- Ensure the `Point` member order `{ x, y, label }` is preserved when using structured bindings.
- If tests fail due to Google Test configuration, verify include/lib paths or use vcpkg to install `gtest`.

Reporting issues
- Please open GitHub Issues for bugs or test failures and include test output and build configuration details.
