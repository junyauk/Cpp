# 03_Optional

This project demonstrates practical usages of `std::optional` (C++17) through basic and advanced examples.

Overview
- Basic examples (`OPTIONAL_Basic`):
  - `findValue(const std::string& key)` — search a `std::map` and return `std::optional<int>`.
  - `getValueOrDefault(const std::string& key, int defaultValue)` — use `value_or` to return a default when absent.
  - `setPendingId(std::optional<int> id)` / `isPendingId(int expectedId)` — manage an optional member and check engagement.
- Advanced examples (`OPTIONAL_Advance`):
  - `chainedProcessing(int initialValue)` — manual monadic chaining across stages (simulates `and_then`).
  - `checkMoveCost(std::optional<LargeData>&& optData)` — demonstrate in-place construction and move semantics when extracting from an optional.
  - `checkExceptionSafety(const std::optional<int>& opt)` — show exception behavior of `value()` and handling `std::bad_optional_access`.

Files
- `Optional_Basic.h` / `Optional_Basic.cpp` — basic patterns: `findValue`, `value_or`, optional member handling.
- `Optional_Advance.h` / `Optional_Advance.cpp` — advanced patterns: chaining, move-cost checks, exception safety.
- `03_OptionalTest/Optional_AdvanceTest.cpp` — unit tests exercising advanced behaviors.

Requirements
- OS: Windows 10/11
- IDE: __Visual Studio 2022__
- Compiler: MSVC with C++17 (ISO C++17)
- Google Test for test projects (if running tests)

Build
1. Open the solution or project folder in Visual Studio 2022.  
2. Ensure the C++ language standard is set to ISO C++17: Project Properties → __C/C++ → Language → C++ Language Standard__ → `ISO C++17`.  
3. Build the solution (Right-click solution → Build Solution).

Examples (API)
#include "Optional_Basic.h" #include "Optional_Advance.h"
int main() { OPTIONAL_Basic::Optional_Basic basic;
// findValue
auto v = basic.findValue("Alice");
if (v) { /* use v.value() */ }

// getValueOrDefault
int id = basic.getValueOrDefault("Unknown", -1);

// pending ID
basic.setPendingId(123);
bool pending = basic.isPendingId(123);

// Advanced: chainedProcessing
OPTIONAL_Advance::Optional_Advance adv;
auto res = adv.chainedProcessing(16); // example input

// Advanced: move semantics
std::optional<OPTIONAL_Advance::LargeData> opt{ std::in_place, "Name", 1000 };
std::string movedName = adv.checkMoveCost(std::move(opt));
}

Notes
- `chainedProcessing` uses manual conditional chaining: first stage produces `std::optional<int>`, second stage (`stage2_transform`) returns `std::optional<std::string>`.
- `LargeData` implements copy and move constructors; `checkMoveCost` moves the contained object out of an optional to demonstrate cost differences (moved name contains `"_M"`).
- `checkExceptionSafety` shows that calling `value()` on a disengaged `std::optional` throws `std::bad_optional_access`; the method catches this and returns false.
- This project is educational; adapt patterns to your codebase as needed.

License
- Add your preferred license (e.g., MIT).

