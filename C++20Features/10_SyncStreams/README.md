# 10_SyncStreams

## Overview

This project demonstrates C++20 synchronized output streams using `std::osyncstream`. The examples compare unsafe concurrent writing to shared streams with safe, atomic-flush semantics provided by `std::osyncstream`, showing how to produce consistent multithreaded output.

## Requirements

- C++20-capable compiler (Visual Studio 2022 recommended).
- Standard library with `<syncstream>` support.
- Project configured to use the C++20 language standard.

## Build

1. Open `C++20Features.sln` in Visual Studio 2022.  
2. Ensure the C++ Language Standard is set to C++20 (Project Properties → C/C++ → __Language__ → __C++ Language Standard__).  
3. Build the `10_SyncStreams` project or the entire solution.

Precompiled headers (`pch.*`) are provided and used by the project.

## Contents

- `SyncStreams_Basic.h`  
  - `SyncStreams_Basic::SyncStreamsBasic` demonstrates:
    - `unsafePrintTask(int threadId, std::ostream& os)` — concurrent writes without synchronization.
    - `safePrintTask(int threadId, std::ostream& os)` — uses `std::osyncstream` for atomic per-thread output.
    - `runSafeSynchronization(int numThreads)` — runs multiple threads and returns captured synchronized output.
- `10_SyncStreams.cpp` — small compilation unit for the project.
- `10_SyncStreams.vcxproj` — Visual Studio project file.
- `pch.h` / `pch.cpp` — precompiled header support.

## Tests

- `10_SyncStreamsTest` contains GoogleTest-based unit tests that verify synchronized output behavior and capture results for assertions. Run tests from Visual Studio Test Explorer or execute the produced test binary from the test project's output directory.

## Contributing

- Add focused, deterministic tests for new synchronization scenarios.
- Avoid brittle tests that depend on thread scheduling timing; assert on captured output content and structure instead of timing.
- Document any environment-specific assumptions (console encoding, line endings) in tests and README.

## License

No license file is included by default. Add a `LICENSE` file if you intend to publish or share the repository.