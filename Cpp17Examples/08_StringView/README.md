# 08_StringView

## Overview

This project demonstrates the use of `std::string_view` (C++17) to create non-owning views into character sequences. The samples illustrate creating views from `std::string` and string literals, performing substring and prefix/suffix operations without allocations, and highlight lifetime and safety considerations.

## Features

- Using `std::string_view` to create lightweight, non-owning references to character data.
- Creating views from `std::string` and string literals without copying.
- Substring operations with `substr`, `remove_prefix`, and `remove_suffix` to manipulate views efficiently.
- Searching and comparing using `std::string_view` operations (`find`, `starts_with`, `ends_with` when available in later standards) and interacting with APIs that accept `std::string_view`.
- Converting a `std::string_view` to an owning `std::string` when a persistent copy is required.

## Public API (summary)

This project provides utility examples that demonstrate typical usage patterns of `std::string_view`. Typical snippets include:

- Creating a view: `std::string_view v = str;` or `std::string_view v = "literal";`
- Taking a prefix/suffix: `v.remove_prefix(n);`, `v.remove_suffix(n);`
- Creating a substring: `auto sub = v.substr(pos, count);` (note: `substr` returns a `std::string_view`).
- Converting to owning string: `std::string s(v);`

Specific function and file names in this project are intended as small, self-contained examples and may be found in the `08_StringView` project folder.

## Requirements

- Visual Studio with C++17 support (MSVC toolset compatible with C++17).

## Building

Open the solution or the `08_StringView` project in Visual Studio and build using the IDE. Select the desired configuration (Debug or Release) and platform, then build the project. The produced executable will be located in the project's output directory (for example, `Debug\` or `Release\` under the project folder).

## Running

Run the produced executable from the project's output directory or launch it from Visual Studio. The samples are lightweight and print demonstration output to the console or are primarily intended for unit tests.

## Tests

If a corresponding test project `08_StringViewTest` exists, use Visual Studio's Test Explorer to run the unit tests. If no test project is present, consider adding tests that validate:

- Views created from `std::string` remain valid only while the source string remains alive.
- `remove_prefix`/`remove_suffix` behavior and `substr` correctness.
- Conversions from `std::string_view` to `std::string` produce expected contents.

## Notes and Caveats

- `std::string_view` does not own memory. Never return a `std::string_view` that points to a local `std::string` or temporary; ensure the referenced data outlives the view.
- When interfacing with APIs that require persistent storage, convert to `std::string`.
- `std::string_view` operations are efficient and avoid allocations when used correctly.
- Prefer `std::string_view` for read-only string parameters to avoid unnecessary copies when API compatibility permits.

## License

See the repository `LICENSE` file for license details.