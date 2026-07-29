# 06_ThreeWayComp

## Overview

This project demonstrates the C++20 three-way comparison operator (`<=>`, "spaceship operator") and the automatically generated equality operator. It shows how defaulted comparisons enable concise, correct, and consistent ordering and equality semantics for aggregate-like types.

## Requirements

- C++20-capable compiler (Visual Studio 2022 recommended).
- Project configured to use the C++20 language standard (`__C++ Language Standard__` → `C++20`).

## Build

1. Open `C++20Features.sln` in Visual Studio 2022.  
2. Ensure the project uses `__C++ Language Standard__` = `C++20`.  
3. Build the `06_ThreeWayComp` project or the entire solution.

Precompiled headers (`pch.*`) are provided for convenience.

## Contents

- `ThreeWayComp_Basic.h`  
  - `ThreeWayComp_Basic::UserProfile` — example struct with members (`m_id`, `m_name`, `m_score`) and a defaulted `operator<=>` returning `std::partial_ordering`.
  - `ThreeWayComp_Basic::ComparisonBasic` — helper methods demonstrating:
    - `isLessThan(const UserProfile&, const UserProfile&)`
    - `isEqual(const UserProfile&, const UserProfile&)`
    - `isGreaterOrEqual(const UserProfile&, const UserProfile&)`

- `06_ThreeWayComp.vcxproj` — Visual Studio project file.
- `pch.h` / `pch.cpp` — precompiled header support.

## Tests

- `06_ThreeWayCompTest` contains GoogleTest-based unit tests validating comparison and equality semantics produced by the defaulted `<=>` implementation.

## Contributing

- Add focused examples that clarify comparison categories (`strong`, `weak`, `partial`) when relevant.
- Add unit tests for any new comparison logic or edge cases.
- Prefer clearly named members and document comparison expectations in header comments.

## License

No license file is included. Add a `LICENSE` file if you intend to publish or share the repository.