# 02_Ranges

## Overview

This project demonstrates core C++20 Ranges and Views features with minimal, focused examples. The intent is to show idiomatic usage of lazy views and ranges-aware algorithms for common data-processing patterns.

## Requirements

- C++20-capable compiler (Visual Studio 2022 recommended).
- Project configured to use the C++20 language standard.

## Build

Open `C++20Features.sln` in Visual Studio 2022 and build the `02_Ranges` project. Ensure the C++ language standard is set to C++20 (Project Properties → C/C++ → __Language__).

## Contents

- `Ranges_Basic.h`
  - `Range_Basic::RangeBasic` — utility class demonstrating:
    - `std::string processPipeline(const std::vector<int>& data) const`  
      Uses `std::views::filter` and `std::views::transform` to build a lazy pipeline and returns results as a space-separated string.
    - `int countTarget(const std::vector<int>& data) const`  
      Uses `std::ranges::count` to count occurrences of a target value.
    - `int sumFirstN(const std::vector<int>& data, size_t n) const`  
      Uses `std::views::take` and `std::accumulate` over the view to sum the first `n` elements.

- `02_Ranges.vcxproj` — Visual Studio project file.
- `pch.h` / `pch.cpp` — precompiled headers used by the project.

## Tests

- `02_RangesTest` contains GoogleTest-based unit tests verifying pipeline behavior, counting, and summation logic.

## Contributing

- Keep examples concise and focused on demonstrating a single concept.
- Add unit tests for any new behavior.
- Prefer clear, idiomatic use of standard ranges and views.

## License

No license file is included. Add a `LICENSE` file if you intend to publish or share the repository.