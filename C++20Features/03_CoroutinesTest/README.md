# 03_CoroutinesTest

## Overview

This project contains unit tests for the `03_Coroutines` examples. Tests validate coroutine behavior, generator semantics, and correct state preservation across suspensions.

## Requirements

- C++20-capable compiler (Visual Studio 2022 recommended).
- GoogleTest framework (NuGet package included in the solution under `packages/`).

## Build

1. Open `C++20Features.sln` in Visual Studio 2022.  
2. Ensure the C++ Language Standard is set to C++20 (Project Properties → C/C++ → __Language__ → __C++ Language Standard__).  
3. Build the `03_CoroutinesTest` project or the entire solution. NuGet packages should be restored automatically if required.

Precompiled headers (`pch.*`) are provided and used by the project.

## Tests

The test suite verifies:
- Correct values yielded by finite coroutine generators.
- Behavior for empty or zero-length sequences.
- Fibonacci generator correctness and sequence limits.
- State preservation across resumptions for generators.
- Behavior of infinite generators when externally controlled by the consumer.

Run tests from Visual Studio Test Explorer or execute the produced test binary from the project's output directory (Debug/Release).

## Notable files

- `03_CoroutinesTest.vcxproj` — Visual Studio project file for tests.  
- `03_CoroutinesTest.cpp` — GoogleTest-based test implementations.  
- `pch.h` / `pch.cpp` — Precompiled header support.

## Contributing

- Add focused tests that validate a single behavior or edge case.
- When adding coroutine examples, include corresponding unit tests here.
- Keep tests deterministic and avoid external dependencies.

## License

No license file is included by default. Add a `LICENSE` file if you intend to publish or share the repository.