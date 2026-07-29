# 02_IfSwitchInit

This project demonstrates C++17 `if`-initializer and `switch`-initializer usage through three concise examples.

Overview
- Example 1: `getValueIfKeyExists(int key)` — uses an `if`-initializer with `std::map::find` to check presence and return an `std::optional<std::string>`.
- Example 2: `calculateMetricIfValid(int rawValue, int threshold)` — uses an `if`-initializer to create a short-lived `ComplexMetric` object (RAII) and return a value only when a condition is met.
- Example 3: `processStatusCode(int initialValue)` — uses a `switch`-initializer to process a status code returned from a helper function with limited scope.

Files
- `IfSwitchInit_Basic.h` — Declarations for `IFSWITCHINIT_Basic::IfSwitchInit_Basic` and `ComplexMetric`.
- `IfSwitchInit_Basic.cpp` — Implementations showing:
  - `getValueIfKeyExists` (lines demonstrating `if (auto it = map.find(...); it != map.end())`)
  - `calculateMetricIfValid` (lines demonstrating `if (ComplexMetric metric(rawValue); metric.getValue() > threshold)`)
  - `processStatusCode` (lines demonstrating `switch (int code = getStatusCode(initialValue); code)`)
- `../02_IfSwitchInitTest/IfSwitchInitTest.cpp` — Unit tests (Google Test) for the above behaviors.

Requirements
- Windows 10/11
- Visual Studio 2022
- MSVC with C++17 (ISO C++17)
- Google Test for test project (if running tests)

Build
1. Open the solution or project folder in Visual Studio 2022.
2. Ensure C++ language standard is set to ISO C++17:
   Project Properties → C/C++ → Language → C++ Language Standard → `ISO C++17`.
3. Build the solution (Right-click solution → Build Solution).

Quick usage examples
#include "IfSwitchInit_Basic.h"
int main() { IFSWITCHINIT_Basic::IfSwitchInit_Basic obj;
// 1) map find + if-initializer
auto val = obj.getValueIfKeyExists(5);
if (val) { /* use val.value() */ }

// 2) limited-scope RAII object with if-initializer
auto metric = obj.calculateMetricIfValid(10, 15);
if (metric) { /* use metric.value() */ }

// 3) switch-initializer
std::string status = obj.processStatusCode(1);
}


Notes
- `ComplexMetric` demonstrates limiting object scope and deterministic destruction via RAII.
- `switch`-initializer restricts the `code` variable scope to the switch block.
- The project is educational: patterns shown are safe to adapt to real codebases.

License
- Add preferred license (e.g., MIT).

