# 10_NonTypeTemplate

This project demonstrates C++17 non-type template parameter (NTTP) techniques, including `auto` NTTPs, pointer/reference NTTPs compatible with C++17, compile-time hashing, and unifying heterogeneous compile-time ranges. The examples highlight practical trade-offs and patterns for using NTTPs in both small utilities and reusable components.

Overview
- Purpose and common scenarios
  - Show how values (integral, pointer, bool, etc.) can be used as template parameters to perform compile-time computations and generate strongly-typed constructs.
  - Demonstrate C++17-compatible NTTPs: `auto` NTTP deduction, integral NTTPs, and pointer NTTPs that reference objects with external linkage (e.g., `const char*` string literals with linkage).
  - Provide compile-time utilities (e.g., FNV‑1a hashing for string literals) and examples where NTTPs produce zero‑overhead compile-time constants used in runtime checks.
  - Illustrate how NTTPs can unify heterogeneous data (e.g., `Range<Start, End>`) to provide a consistent runtime interface while keeping computations at compile time.

- Key concepts demonstrated
  - `template<auto N>`: deducing the NTTP's type and accessing it with `decltype(N)`.
  - Pointer NTTPs in C++17: using `const char*` and explicit size NTTP to represent string-literal keys; constraints on external linkage are shown and respected.
  - Compile-time hashing: `ConstexprHash<Str, Size>::value` computed via a constexpr FNV-1a implementation for use as compile-time keys.
  - `Range<Start, End>` using `auto` NTTPs to accept different integral types while enforcing compile-time checks (`static_assert`) and exposing a unified `ValueType`.
  - `createSizeArray<N>()` pattern: NTTPs drive type construction (e.g., `std::array<int, N>`).

Files
- `NonTypeTemplate_Basic.h`
  - `CompileTimeValue<auto N>`: basic `auto` NTTP usage and `toString()` helpers for runtime testing.
  - `ArrayMultiplier<int Size, auto Multiplier>`: demonstrates mixed NTTP types for compile-time parameters and runtime operations.
  - `AutoNTTP_Basic` helper with example entry points.
- `NonTypeTemplate_Advance.h`
  - `fnvla_hash_32` constexpr FNV-1a hash and `ConstexprHash<const char*, size_t>` for compile-time string hashing (C++17 compatible).
  - `Range<Start, End>`: NTTP-driven, type-deduced range with compile-time assertions and runtime info.
  - `NonTypeTemplate_Advance` utilities: `createSizeArray<N>()`, `getHashValue(std::string_view)` for runtime comparison, and `createRange<S, E>()`.
- `10_NonTypeTemplateTest/NonTypeTemplate_AdvanceTest.cpp`
  - Unit tests validating compile-time hashes, array size deduction, and `Range` behavior for different NTTP types (int and char).

Requirements
- Windows 10/11
- Visual Studio 2022
- MSVC with C++17 support (ISO C++17)
- Google Test for running the test project (if desired)

Build
1. Open the solution or the project folder in Visual Studio 2022.  
2. Ensure projects target ISO C++17: Project Properties → C/C++ → Language → C++ Language Standard → `ISO C++17`.  
3. Build the solution (Right‑click solution → `Build Solution`).

Notes and best practices
- In C++17, pointer/reference NTTPs must refer to entities with external linkage. The test suite defines `static constexpr` char arrays with appropriate linkage for use as NTTPs.
- Use `auto` NTTP where you want the compiler to deduce the exact NTTP type, but document expected types (integral, pointer) to avoid surprises.
- Prefer compile-time hashing and NTTP-based keys when you need zero-overhead lookup keys or generated identifiers, but be mindful of linkage and ODR rules.
- When unifying heterogeneous compile-time parameters (e.g., `Range` with `char` vs `int`), provide `ValueType` typedefs and `static_assert` checks to make constraints explicit.
- Add license information as needed (e.g., MIT).