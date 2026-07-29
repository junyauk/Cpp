# 01_FinancialModule

## Overview

`01_FinancialModule` contains a small set of financial utility implementations intended to demonstrate modular, reusable C++ code patterns. The project focuses on clear, testable functions suitable for inclusion in larger systems.

## Requirements

- C++20-capable compiler (Visual Studio 2022 recommended).
- Project configured to use the C++20 language standard.

## Build

1. Open `C++20Features.sln` in Visual Studio 2022.
2. Ensure the C++ Language Standard is set to C++20 (Project Properties → C/C++ → __Language__ → __C++ Language Standard__).
3. Build the `01_FinancialModule` project or the entire solution.

Precompiled headers (`pch.*`) are provided and used by the project.

## Contents

- `FinancialUtils.cpp` — Implementation of financial helper functions.
- `framework.h` — Project-level includes and configuration.
- `pch.h` / `pch.cpp` — Precompiled header files.
- `01_FinancialModule.vcxproj` — Visual Studio project file.

The project is organized to separate interface and implementation and to facilitate unit testing and reuse.

## Tests

No dedicated test project is included specifically under `01_FinancialModule`. Add unit tests to an existing test project (for example, `01_ModulesTest`) or create a new test project to validate the utilities.

## Contributing

- Keep changes focused and small.
- Add unit tests for any behavioral changes or new utilities.
- Favor clarity, deterministic behavior, and documented edge cases.

## License

No license file is included by default. Add a `LICENSE` file if you intend to publish or share the repository.