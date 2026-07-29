# 01_StructuredBindings

## Overview

This project demonstrates C++17 structured bindings through small, focused utilities and helpers. It shows how to work with tuples, pairs, maps, and simple user-defined types using structured binding syntax to simplify element access and return-value unpacking.

## Features

- Lightweight types and factory functions that illustrate structured bindings:
  - `Point` with lexicographical comparison using `std::tie`.
  - `Employee` aggregate type.
- Helper functions returning and consuming `std::tuple`, `std::pair`, and container iterators.
- Examples of using structured bindings for map insertion and range-based loops over associative containers.

## Public API (summary)

- Types
  - `struct Point`  
    - Members: `int x`, `int y`  
    - `bool operator<(const Point& other) const` — compares using `std::tie(x, y)`.
  - `struct Employee`  
    - Members: `int id`, `std::string name`, `double salary`

- Functions
  - `Point make_point(int x, int y)` — create a `Point`.
  - `std::tuple<int, std::string> make_tuple_example(int num, const std::string& text)` — returns a simple tuple.
  - `std::pair<std::map<std::string, int>::iterator, bool> insert_score(std::map<std::string, int>& scores, const std::string& name, int score)` — inserts into a `std::map` and demonstrates unpacking the result via structured bindings.
  - `std::map<std::string, int>::iterator find_score(std::map<std::string, int>& scores, const std::string& name)` — finds an entry in the map.
  - `std::pair<std::vector<std::string>, std::vector<int>> map_loop_example(std::unordered_map<std::string, int> data)` — iterates the map using structured bindings and returns separated vectors of keys and values.
  - `Employee make_employee(int id, std::string name, double salary)` — create an `Employee`.

## Requirements

- Visual Studio with C++17 support (MSVC toolset compatible with C++17).
- No external libraries required.

## Building

Open the solution or the project containing `01_StructuredBindings` in Visual Studio and build using the IDE. Select the desired configuration (Debug or Release) and platform, then build the project. The produced executable will be located in the project's output directory (for example, `Debug\` or `Release\` under the project folder).

## Running

Run the produced executable from the project's output directory or launch it from Visual Studio. The project prints diagnostic output illustrating structured binding usage.

## Tests

No automated tests are included. Add tests if you want to validate behavior and examples.

## Notes

- Follow repository-wide coding standards in `.editorconfig` and `CONTRIBUTING.md`.
- The code targets C++17 and uses language features introduced in that standard (structured bindings, tuple utilities).

## License

See the repository `LICENSE` file for license details.