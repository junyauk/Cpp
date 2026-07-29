# 01_StructuredBindingsTest

## Overview

This project contains unit tests for the `01_StructuredBindings` examples. Tests are written with Google Test and validate decomposition of aggregates, tuples, and associative-container operations using C++17 structured bindings.

## Requirements

- Visual Studio with C++17 support (MSVC toolset compatible with C++17).
- Google Test framework integrated into the test project (the project currently includes `gtest` headers).

## Building

Open the solution or the test project `01_StructuredBindingsTest` in Visual Studio and build the solution. Ensure the test project compiles successfully.

## Running Tests

- Use Visual Studio's __Test Explorer__ to discover and run the tests.
- Alternatively, run the produced test executable from the test project's output directory (for example, `Debug\` or `Release\`) to run all tests on the command line.

## What the tests cover

- `Point` decomposition and lexicographical comparison.
- `std::tuple` decomposition returned by `make_tuple_example`.
- Map insertion unpacking using structured bindings (`insert_score`) and behavior when inserting duplicates.
- Map lookup with if-init and decomposing `std::map` iterators.
- `Employee` aggregate decomposition.

## Notes

- Follow the repository-wide coding standards in `.editorconfig` and `CONTRIBUTING.md`.
- This project targets C++17 language features (structured bindings, tuple utilities).

## License

See the repository `LICENSE` file for license details.