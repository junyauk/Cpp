# 07_DesignatedInit

## Overview

This project demonstrates C++20 designated initializers for aggregates and highlights ordering rules and correct usage patterns. Examples illustrate how designated initializers interact with aggregate layout and compiler enforcement of initializer order.

## Requirements

- C++20-capable compiler (Visual Studio 2022 recommended).
- Project configured to use the C++20 language standard.

## Build

1. Open `C++20Features.sln` in Visual Studio 2022.  
2. Ensure the C++ Language Standard is set to C++20 (Project Properties → C/C++ → __Language__ → __C++ Language Standard__).  
3. Build the `07_DesignatedInit` project or the entire solution.

Precompiled headers (`pch.*`) are provided and used by the project.

## Contents

- `DesignatedInit_Basic.h`  
  - Aggregate types and functions illustrating designated initializer syntax.
  - Utility routines that construct example aggregates showing full and partial initialization and the compiler-enforced ordering constraints.

- `07_DesignatedInit.vcxproj` — Visual Studio project file.  
- `pch.h` / `pch.cpp` — precompiled header support.

## Tests

- `07_DesignatedInitTest` contains GoogleTest-based unit tests that verify correct initialization behavior and document compile-time rules (some cases are intentionally compile-time errors and are explained in comments/tests).

## Contributing

- Add focused examples that clarify initializer order, defaults, and aggregate evolution.
- When adding new cases, include tests that document expected compile-time diagnostics or runtime behavior.
- Keep examples minimal and well-commented for educational clarity.

## License

No license file is included by default. Add a `LICENSE` file if you intend to publish or share the repository.