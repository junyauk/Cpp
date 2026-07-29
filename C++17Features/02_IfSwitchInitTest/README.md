# 02_IfSwitchInitTest

This test project contains Google Test unit tests for the `02_IfSwitchInit` examples.

Contents
- `IfSwitchInitTest.cpp` — Tests include:
  - `GetValueIfKeyExists_Found` and `GetValueIfKeyExists_NotFound` (map find with `if`-initializer).
  - `CalculateMetricIfValid_Valid` and `CalculateMetricIfValid_Invalid` (RAII object with `if`-initializer).
  - `ProcessStatusCode_CaseMatch` and `ProcessStatusCode_DefaultCase` (switch-initializer behavior and cases).

Requirements
- Visual Studio 2022
- Google Test configured in the solution (vcpkg, submodule, or vendor)
- MSVC with C++17 support

Build and run tests
- Build the solution in Visual Studio (Right-click solution → Build Solution).
- Run tests from Test Explorer (Test → Test Explorer) or execute the test project binary:
  Example: `.\02_IfSwitchInitTest\Debug\02_IfSwitchInitTest.exe`

Expected behaviors summarized
- `getValueIfKeyExists(5)` returns `"Five"`; a missing key returns `std::nullopt`.
- `calculateMetricIfValid(10, 15)` returns `20`; smaller input returns `std::nullopt`.
- `processStatusCode` returns case-specific strings for `-1`, `0`, `10`, and a formatted default message for other codes.

Notes
- If tests fail, confirm Google Test include/libs and C++17 configuration.
- Test fixture resets and reconstructs `IfSwitchInit_Basic` before each test to ensure isolation.