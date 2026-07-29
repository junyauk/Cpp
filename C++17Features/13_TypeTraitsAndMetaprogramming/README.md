# 13_TypeTraitsAndMetaprogramming

This project demonstrates C++17 type traits and template metaprogramming techniques. It contains focused examples that explain how to query, transform, and compose types at compile time, how to write SFINAE-safe utilities, and how to apply modern idioms such as the detection idiom, `std::void_t`, `constexpr if`, and variable templates to produce clear, maintainable metaprogramming code.

Overview (expanded)
- Purpose and common scenarios
  - Teach practical compile‑time type inspection and transformation techniques used in libraries and generic code.
  - Show safe feature-detection and overload selection (SFINAE, detection idiom, `std::void_t`) to write portable, adaptable templates.
  - Demonstrate metafunction composition (alias templates, `std::conditional_t`, `std::enable_if_t`, `std::conjunction` / `std::disjunction`) and utilities for building higher-level generic abstractions.
  - Provide patterns for type lists, type traits wrappers, and lightweight compile‑time computations that improve runtime performance and API safety.

- Key concepts demonstrated
  - Fundamental traits: `std::is_same`, `std::is_integral`, `std::is_convertible`, `std::remove_reference_t`, `std::decay_t`, `std::remove_cv_t`, `std::enable_if_t`, `std::integral_constant`.
  - Detection idiom and `std::void_t`: writing `is_detected` / `detected_t` style utilities to probe for member functions, nested types, or expression validity without causing hard errors.
  - Expression SFINAE vs. `constexpr if`: selecting implementations based on compile‑time properties while keeping diagnostics readable.
  - Variable templates and alias templates: concise trait aliases (e.g., `is_callable_v`, `void_t_t`) for cleaner code.
  - Metafunction composition: using `std::conditional_t`, `std::conjunction`, `std::disjunction`, and custom combinators to build complex trait logic.
  - Type lists and simple compile‑time algorithms: type counting, filtering, and mapping using variadic templates.
  - Best practices for API design: prefer small, documented trait utilities; prefer `std::enable_if_t` in the form of alias templates or `constexpr if` for readability; wrap complex metaprogramming behind named helpers.

Files
- `TypeTraits_Basic.h` / `TypeTraits_Basic.cpp`
  - Basic trait examples and helper aliases demonstrating `std` trait usage and simple compile‑time checks.
- `TypeTraits_Advance.h` / `TypeTraits_Advance.cpp`
  - Detection idiom utilities, `is_callable` / `is_detected` helpers, type-list utilities, and examples of composing traits for more advanced selection logic.
- `13_TypeTraitsAndMetaprogrammingTest/` — unit tests (Google Test)
  - Tests validating trait behavior, detection outcomes, overload resolution, and correctness of type-list operations.

Requirements
- Windows 10/11
- Visual Studio 2022
- MSVC with C++17 support (ISO C++17)
- Google Test for the test project (if running tests)

Build
1. Open the solution or the project folder in Visual Studio 2022.  
2. Ensure C++ language standard is set to ISO C++17:
   Project Properties → `C/C++` → `Language` → `C++ Language Standard` → `ISO C++17`.  
3. Build the solution (Right‑click solution → `Build Solution`).

Notes and best practices
- Prefer small, well‑named trait helpers to hide metaprogramming complexity from callers.
- Use `std::void_t` and the detection idiom to probe for capabilities rather than trying to instantiate ill-formed expressions directly.
- Use `constexpr if` where available to simplify overload selection and improve diagnostics.
- Document expected semantics of each trait and the constraints it enforces; failing `static_assert` messages should be informative.
- When possible, prefer `std::variant`/`std::optional`/`std::function` and clearer runtime abstractions instead of excessive compile‑time machinery—use metaprogramming where it provides concrete compile‑time benefits.

License
- Add your preferred license (e.g., MIT).