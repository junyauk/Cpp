# 01_ConceptsAndRanges

This project demonstrates a comparison between pre-C++20 algorithmic styles and C++20 ranges/concepts. It is header-centric and intended as a compact exercise collection illustrating modern C++20 idioms.

## Overview

- Key file: `Combined_Processor.h`
- Purpose: Show equivalent processing tasks implemented with:
  - a classical iterator/algorithm style (`Cpp17Processor`)
  - a C++20 ranges-and-concepts style (`Cpp20Processor`)
- Core types:
  - `DataEntry` — simple aggregate with `id`, `value`, and `tag`. Uses defaulted three-way comparison (`operator<=>`).
  - `IProcessor` — abstract interface declaring a set of processing operations (filtering, summing, slicing, concatenation, searching, move semantics, stride summation, etc.).
  - `Cpp17Processor` — concrete implementation using classic STL algorithms and manual iterator logic.
  - `Cpp20Processor` — concrete implementation leveraging `std::ranges`, `std::views`, constrained templates and `requires` clauses.

## Demonstrated C++20 features

- Concepts and constrained templates (examples: `NumericRange`, `SortableRange`, `RandomAccessRange`, `BidirectionalRange`, `DataEntryPredicate`, etc.)
- Ranges and views (`std::views::filter`, `transform`, `drop`, `reverse`, `take`)
- `std::ranges` algorithms and utilities (`sort`, `unique`, `find_if`, `copy`, `move`, `distance`, `size`)
- Three-way comparison (`operator<=>`) and defaulted comparisons
- Correlation between iterator-based and view-based pipelines
- Writing generic functions with `requires` and composed constraints

## Requirements

- A C++20-compliant compiler (MSVC in Visual Studio 2022, or recent GCC/Clang with `-std=c++20`)
- Visual Studio 2022 or a CMake-capable build environment

## Build notes

- The code is header-only. To build examples/tests, include the header(s) in a C++20 target and set the language standard to C++20.
- Visual Studio: Project Properties → C/C++ → __Language__ → set `C++ Language Standard` to __ISO C++20 Standard (/std:c++20)__.
- CMake: set `CMAKE_CXX_STANDARD=20` or equivalent toolchain configuration.

## Notes

- The project focuses on idiomatic comparisons and teaching points rather than on a single runnable application; include the header into test or example harnesses as needed.
- Update this README if additional source or test files are added to the project.

## Contributing

Follow repository conventions and ensure all additions compile with C++20.