# 09_MapSet

## Overview

This project demonstrates usage patterns and APIs of ordered (`std::map`, `std::multimap`) and unordered (`std::unordered_map`, `std::unordered_multimap`) associative containers in C++17. It covers insertion variants, lookup, range queries (`lower_bound`, `upper_bound`, `equal_range`), bucket and load-factor behavior for hash tables, and common iteration patterns including structured bindings.

## Features

- `MapBasics` utilities
  - `insertExamples()` — shows `insert`, `operator[]`, and `emplace`.
  - `findExample()` / `atExample()` — lookup using `find` and `at` with `std::optional` results.
  - `eraseExamples()`, `updateExamples()` — erase and update idioms (`operator[]`, `try_emplace`).
  - `sumValues()`, `orderedKeys()`, `unorderedKeys()` — iteration and aggregation examples using structured bindings.

- `01_TryEmplace` and `02_InsertOrAssign`
  - Demonstrate `try_emplace` (no overwrite) and `insert_or_assign` (overwrite) semantics for `std::map` and `std::unordered_map`, and show iteration results.

- Range queries and multimap usage
  - `MapSetLowerUpper` demonstrates `lower_bound`, `upper_bound`, `equal_range` and bulk erase using iterator ranges.
  - `ExampleOfEqualRangeOfMultiMap` and `ExampleOfEqualRangeOfUnorderedMultiMap` show retrieving all values for a given key.

- Unordered map bucket and performance helpers
  - `MapSetUnorderedPref` shows `reserve`, `rehash`, `bucket_count`, and `load_factor` effects.
  - `Warehouse` (in `Warehouse.h`) wraps an `std::unordered_map` and exposes bucket inspection helpers and load-factor-related methods.

## Public API (summary)

- `MapSetExamples::MapBasics` (class):
  - `static std::map<std::string,int> insertExamples()`
  - `static std::optional<int> findExample(const std::map<std::string,int>&, std::string&)`
  - `static std::optional<int> atExample(const std::map<std::string,int>&, std::string&)`
  - `static std::map<std::string,int> eraseExamples()`
  - `static std::map<std::string,int> updateExamples()`
  - `static int sumValues(const std::map<std::string,int>&)`
  - `static bool capacityExamples()`
  - `static std::vector<std::string> orderedKeys()`
  - `static std::vector<std::string> unorderedKeys()`

- `MapSetExamples::TestTryEmplaceMap()` / `TestTryEmplaceUnorderedMap()`
- `MapSetExamples::TestInsertOrAssignMap()` / `TestInsertOrAssignUnordered()`
- `MapSetExamples::ExampleOfLowerAndUpper()`, `ExampleOfEqualRangeOfMultiMap()`, `ExampleOfEqualRangeOfUnorderedMultiMap()`
- `MapSetExamples::getLoadFactor(size_t, size_t)`, `ExampleOfUnorderedMapBuckets()`
- `MapSetExamples::Warehouse` class with:
  - `addProduct`, `getStock`, `bucketCount`, `bucket`, `bucketSize`, `listBucket`, `inspectBucket`, `rehash`, `reserve`, `getCurrentLoadFactor`, `getMaxLoadFactor`, `setMaxLoadFactor`

## Requirements

- Visual Studio with C++17 support (MSVC toolset compatible with C++17).
- No external libraries required.

## Building

Open the solution or the project containing `09_MapSet` in Visual Studio and build using the IDE. Select the desired configuration (Debug or Release) and platform. The produced binaries will be in the project's output directory (for example, `Debug\` or `Release\` under the project folder).

## Running

Run the produced executable from the project's output directory or start it from Visual Studio. Many utilities are header-inline helpers that return strings or containers and are primarily intended for unit tests and small demos.

## Tests

A test project `09_MapSetTest` is included (`09_MapSetTest\09_MapSetTest.cpp`). It covers:
- Insert/emplace semantics and structured-binding unpacking for insertion results.
- `try_emplace` and `insert_or_assign` behaviors for both ordered and unordered maps.
Use Visual Studio's Test Explorer to discover and run the tests, or execute the test binary from the output folder.

## Notes

- Prefer `try_emplace` when you want to construct an element in-place and avoid overwriting existing values.
- Use `insert_or_assign` when you explicitly want to overwrite or insert.
- For performance with `std::unordered_map`, use `reserve`/`rehash` to control bucket counts and reduce rehashing.
- Range-based erase using `erase(lower, upper)` is more efficient than erasing keys one-by-one when removing contiguous key ranges from ordered maps.
- Follow repository-wide coding standards in `.editorconfig` and `CONTRIBUTING.md`.

## License

See the repository `LICENSE` file for license details.