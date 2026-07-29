# 11_InlineVariables

This project demonstrates C++17 `inline` variables for header-only definitions and safe cross-translation-unit sharing of variables and static members. Examples cover `inline` global constants, `inline static` class members, complex header-defined objects, and patterns for header-only library design.

Overview
- Purpose and common scenarios
  - Use `inline` variables to define non-`constexpr` or complex objects in headers without violating the One Definition Rule (ODR).
  - Provide header-only shared state (configuration maps, constant containers) safely across multiple translation units.
  - Replace separate source-file definitions for static members with `inline static` members defined directly in class bodies.
  - Illustrate runtime-initialized inline variables (non-`constexpr`) and compare with `constexpr` semantics.
- Key concepts demonstrated
  - `inline` variable semantics: single shared instance across TUs, safe inclusion in multiple translation units.
  - `inline static` member variables: define and initialize static members inside class declarations (no out-of-class definition required).
  - Header-only design: define complex objects (e.g., `std::map`, `std::vector`) in headers using `inline` to keep code header-only and ODR-compliant.
  - Interaction with object lifetime and thread-safety: runtime initialization order and modification patterns for inline non-const variables.
- Best practices
  - Prefer `constexpr` for compile-time constants where possible; use `inline` for non-`constexpr` header-defined objects.
  - Keep mutable inline globals limited and well-documented to avoid hidden shared-state issues.
  - Provide accessor/modifier functions to encapsulate and document expected usage of shared inline variables.

Files
- `InlineVariables_Basic.h` / `InlineVariables_Basic.cpp`
  - `VERSION_STRING` (inline global constant), `CONFIG_DEFAULT` (inline `std::map`), and `Counter::instanceCount` (inline static member).
  - Utility functions demonstrating access across translation units (`access_inline_counter`, `get_inline_timeout`).
- `InlineVariables_Advance.h`
  - `Configuration` class and `SHARED_CONSTANTS` demonstrating non-`constexpr` inline variables and header-only shared data.
- `11_InlineVariablesTest/InlineVariablesTest.cpp`
  - Unit tests validating access, ODR-compliance, lifetime and single-instance behavior.

Requirements
- Windows 10/11
- Visual Studio 2022
- MSVC with C++17 support (ISO C++17)
- Google Test for running unit tests (if desired)

Build
1. Open the solution or project folder in __Visual Studio 2022__.  
2. Ensure C++ language standard: Project Properties → `C/C++` → `Language` → `C++ Language Standard` → `ISO C++17`.  
3. Build the solution (Right‑click solution → `Build Solution`).

Notes
- Inline non-const variables can be modified at runtime; document expected mutation and concurrency semantics.
- `constexpr` variables remain preferable for true compile-time constants; `inline` enables header-only definitions for runtime-initialized objects.
- Add license information as needed (e.g., MIT).