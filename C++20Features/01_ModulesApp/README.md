# 01_ModulesApp

## Overview

`01_ModulesApp` demonstrates module-style organization and modular compilation patterns in modern C++. The project contains small components structured to illustrate separation of interface and implementation, reusable module-like boundaries, and practical build organization for C++20 codebases.

## Requirements

- C++20-capable compiler (Visual Studio 2022 recommended).
- Project configured to use the C++20 language standard.

## Build

1. Open `C++20Features.sln` in Visual Studio 2022.
2. Ensure the C++ Language Standard is set to C++20 (Project Properties → C/C++ → __Language__ → __C++ Language Standard__).
3. Build the `01_ModulesApp` project or the entire solution.

Precompiled headers (`pch.*`) are provided for convenience.

## Contents

- `Modules_Basic.cpp` / `Modules_Basic.h` — Core implementation and header demonstrating modular organization and component interfaces.
- `framework.h` — Project-level includes and common configuration.
- `pch.h` / `pch.cpp` — Precompiled header support.
- `01_ModulesApp.vcxproj` — Visual Studio project file.

The code is organized to emphasize clear interfaces, minimal coupling, and straightforward inclusion into larger projects.

## Tests

- No dedicated test project is bundled specifically with `01_ModulesApp`. Use `01_ModulesTest` or create a new test project to validate behavior if required.

## Contributing

- Keep changes small and focused.
- Add unit tests for new logic or changes to public interfaces.
- Maintain clear separation between interface and implementation.
- Document any public-facing API changes in the repository README or the project's header files.

## License

No license file is included by default. Add a `LICENSE` file if you intend to publish or share the repository.