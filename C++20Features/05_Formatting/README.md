# 05_Formatting

## Overview

This project demonstrates C++20 formatting facilities using `std::format` and related formatting techniques. The examples focus on safe, expressive, and compile-time-friendly formatting of numbers, strings, and chrono types.

## Requirements

- C++20-capable compiler (Visual Studio 2022 recommended).
- Project configured to use the C++20 language standard.

## Build

1. Open `C++20Features.sln` in Visual Studio 2022.  
2. Ensure the C++ Language Standard is set to C++20 (Project Properties → C/C++ → __Language__ → __C++ Language Standard__).  
3. Build the `05_Formatting` project or build the entire solution.

Precompiled headers (`pch.*`) are provided and used by the project.

## Contents

- `Formatting_Basic.h`  
  - `Formatting_Basic::FormattingBasic` class demonstrating:
    - Basic formatting with implicit argument indexing.
    - Numeric formatting (precision, binary formatting, sign control).
    - Padding, alignment, and width specification.
    - Chrono/time formatting using `std::format`, with platform-specific handling for `localtime_s` / `localtime_r`.

- `05_Formatting.cpp` — small compilation unit for the project.
- `05_Formatting.vcxproj` — Visual Studio project file.
- `pch.h` / `pch.cpp` — precompiled header support.

## Tests

- `05_FormattingTest` contains GoogleTest-based unit tests that validate formatting outputs and ensure deterministic behavior across target platforms.

## Contributing

- Keep changes focused and maintain clear, deterministic formatting examples.
- Add unit tests for any new formatting utilities or behaviors.
- Prefer `std::format` idioms and avoid platform-specific behavior without explicit guarding and documentation.

## License

No license file is included by default. Add a `LICENSE` file if you intend to publish or share the repository.