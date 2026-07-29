# 01_StructuredBinding

This project demonstrates C++17 structured bindings through three focused examples:
1. Using structured binding with `std::pair` returned by `std::map::insert`.
2. Using structured binding to decompose a simple custom `struct` (`Point`).
3. Using structured binding to extract elements from a `std::tuple`.

Files
- `structured_binding_basic.h` — Declaration of `StructuredBinding_Basic` and `StructuredBinding::Point`.
- `structured_binding_basic.cpp` — Implementation demonstrating:
  - `insertToMap(int key, const std::string& value)` — shows structured binding from `std::map::insert`.
  - `getLabelFromStruct(int x, int y, const std::string& label)` — constructs a `Point` and returns its `label` via structured binding.
  - `procssTuple(const std::tuple<std::string, int>& dataTuple)` — extracts tuple elements and returns a combined string.
- `../01_StructuredBindingTest/StructuredBinding_BasicTest.cpp` — Google Test unit tests covering the examples.

Requirements
- Windows 10/11
- Visual Studio 2022
- MSVC with C++17 support (ISO C++17)
- Google Test available for running unit tests (project includes a test project)

Build
1. Open the solution or project in Visual Studio 2022.
2. Ensure each project's C++ language standard is set to ISO C++17:
   Project Properties → C/C++ → Language → C++ Language Standard → `ISO C++17`.
3. Build the solution (Right-click solution → Build Solution).

Run / Usage examples (API)
#include "structured_binding_basic.h"
int main() { STRUCTUREDBINDING_Basic::StructuredBinding_Basic sb;
// 1) insertToMap
bool ok = sb.insertToMap(30, "Thirty"); // returns true if inserted

// 2) getLabelFromStruct
std::string label = sb.getLabelFromStruct(5, 10, "Home"); // returns "Home"

// 3) procssTuple (note: function name in code is `procssTuple`)
std::string combined = sb.procssTuple(std::make_tuple(std::string("Age"), 35)); // "Age,35"
}

Tests
- Unit tests use Google Test and are located in `01_StructuredBindingTest`.
- In Visual Studio: Open Test Explorer (Test → Test Explorer) and run all tests.
- Alternatively, run the test project executable created by the test build.

Notes
- The `Point` struct members are declared in the order `{ x, y, label }`. Structured binding must match this declaration order.
- The project demonstrates practical, small-scale examples intended for learning structured bindings; adapt the patterns for larger codebases as needed.

License
- Add your preferred license information here (e.g., MIT).
