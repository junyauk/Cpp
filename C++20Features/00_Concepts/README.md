# 00_Concepts

## Overview

This project demonstrates C++20 Concepts through a compact set of examples focused on template constraints and overload resolution. It shows how to define custom concepts and how to use standard library concepts to make intent explicit and improve compile-time diagnostics.

## Requirements

- C++20-capable compiler (Visual Studio 2022 recommended).
- Project configured to use the C++20 language standard.

## Build

Open `C++20Features.sln` in Visual Studio and build the `00_Concepts` project. Precompiled headers (`pch.*`) are provided for convenience.

## Contents

- `Concepts_Basic.h`
  - Custom concept `CompareLessGreater<T>` that requires `<` and `>` operations.
  - Class `ConceptsBasic` with the following members:
    - `template<CompareLessGreater T> bool isGreaterThan(const T& a, const T& b) const;`
    - `template<std::equality_comparable T> bool areEqual(const T& a, const T& b) const;`
    - `template<typename T> bool isContainerEmpty(const T& container) const` (requires expression `container.empty()`).
    - Overload examples demonstrating concept-constrained overload resolution:
      - `template<std::integral T> std::string getTypeInfo(const T&) const;`
      - `template<std::floating_point T> std::string getTypeInfo(const T&) const;`
      - Generic fallback `template<typename T> std::string getTypeInfo(const T&) const;`

## Tests

- `00_ConceptsTest` contains GoogleTest-based unit tests exercising the examples and validating behavior and constraints.

## Notable files

- `00_Concepts.vcxproj` — Visual Studio project file.
- `Concepts_Basic.h` — primary header with examples.
- `pch.h` / `pch.cpp` — precompiled header support for the project.
- `00_ConceptsTest/` — test project and supporting files.

## Contributing

- Keep additions focused and minimal.
- Prefer explicit concepts to document template requirements.
- Add unit tests in the `00_ConceptsTest` project for any new examples.

## License

No license file is included. Add a `LICENSE` file if publishing or sharing the repository.