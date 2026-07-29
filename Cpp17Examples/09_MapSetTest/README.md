# 09_MapSetTest

## Overview

This test project contains unit tests for the `09_MapSet` examples. Tests are implemented with Google Test and validate insertion semantics, emplace behavior, and map/unordered_map update idioms.

## Requirements

- Visual Studio with C++17 support (MSVC toolset compatible with C++17).
- Google Test framework integrated into the test project (the project includes `gtest` headers).

## Building

Open the solution or the `09_MapSetTest` project in Visual Studio and build the solution. Ensure the test project compiles successfully.

## Running Tests

- Use Visual Studio's __Test Explorer__ to discover and run the tests.
- Alternatively, run the produced test executable from the test project's output directory (for example, `Debug\` or `Release\`) to run all tests from the command line.

## Tests included

- `MapInsertVariants::InsertAndEmplace` — verifies `insert` and `emplace` semantics and structured-binding unpacking of insertion results; ensures duplicates are not overwritten by `insert`/`emplace`.
- `MapSetExamplesTest::TryEmplace` — validates `try_emplace` behavior for `std::map` and `std::unordered_map`, ensuring existing elements are not replaced and that result iteration contains expected elements.
- `MapSetExamplesTest::InsertOrAssign` — validates `insert_or_assign` semantics to overwrite existing values for both ordered and unordered maps.

## Notes

- Use `try_emplace` to construct elements in-place without overwriting existing entries.
- Use `insert_or_assign` when you need to insert or overwrite an existing element in one operation.
- Tests demonstrate structured bindings for unpacking `std::pair<iterator,bool>` returned by insertion operations.
- Follow repository-wide coding standards in `.editorconfig` and `CONTRIBUTING.md`.

## License

See the repository `LICENSE` file for license details.