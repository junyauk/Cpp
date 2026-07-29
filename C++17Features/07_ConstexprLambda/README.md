# 07_ConstexprLambda

This project demonstrates C++17 constexpr lambda patterns and practical techniques for performing compile‑time and runtime computations using implicitly constexpr lambdas, immediate invocation (IIFE), and constexpr initialization of static data. The examples show both straightforward compile‑time uses and pragmatic workarounds for recursive or more complex computations within the constraints of C++17.

Overview
- Purpose and common scenarios
  - Teach how constexpr lambdas can be used to perform computations that are evaluated at compile time when possible, and fall back to runtime when not.
  - Provide idioms for compile‑time array initialization, inline constexpr member initialization via IIFE, and safe capture of constexpr values.
  - Demonstrate pragmatic approaches for recursive computations when direct constexpr recursive lambdas are awkward in C++17 (use constexpr helper functions or simplified iterative lambdas).

- Key concepts demonstrated
  - Implicit constexpr lambdas in C++17: lambdas used in constexpr contexts can be evaluated at compile time if they meet constexpr requirements.
  - IIFE (Immediately Invoked Function Expression) with constexpr lambda to initialize `inline static constexpr` members and arrays.
  - Compile‑time vs runtime use: show the same lambda used both as a compile‑time initializer and as a runtime callable.
  - Constraints and portability: limitations in C++17 for recursive lambdas; show alternatives (constexpr helper functions or iterative lambdas) and use of `static_assert` to validate compile‑time properties.
  - Safe captures: capturing constexpr values and using them in constexpr contexts.

- Best practices
  - Favor simple, side‑effect‑free computations for compile‑time evaluation; avoid dynamic allocation or non‑constexpr library calls inside constexpr lambdas.
  - When recursion is required, use a constexpr function or a well‑tested Y‑combinator helper compatible with C++17, or restructure the algorithm iteratively.
  - Use `static_assert` to document and verify compile‑time invariants where appropriate.
  - Keep public APIs simple and document whether values are computed at compile time or runtime.

Files
- `ConstexprLambda_Basic.h` — basic examples:
  - runtime/callable constexpr lambda for squaring,
  - compile‑time array initialization using a constexpr lambda IIFE,
  - runtime summation using the constexpr lambda.
- `ConstexprLambda_Advance.h` — advanced examples:
  - `factorial_constexpr_func` helper function and examples of compile‑time initialization,
  - inline `Config` class with `inline static constexpr` member initialization via constexpr lambda IIFE,
  - examples showing capture of constexpr values and compile‑time checks.
- `07_ConstexprLambdaTest/ConstexprLambdaTest.cpp` and `07_ConstexprLambdaTest/ConstexprLambda_AdvanceTest.cpp` — Google Test cases and `static_assert` checks that validate runtime results and compile‑time properties.

Requirements
- Windows 10/11
- Visual Studio 2022
- MSVC with C++17 (set to ISO C++17)

Build
1. Open the solution or the project folder in __Visual Studio 2022__.  
2. Ensure each project uses the C++17 language standard:
   Project Properties → `C/C++` → `Language` → `C++ Language Standard` → `ISO C++17`.  
3. Build the solution (Right‑click solution → `Build Solution`).

Tests
- Unit tests use Google Test and include runtime assertions plus `static_assert` checks to ensure some values are usable in constexpr contexts.
- Run tests via Visual Studio Test Explorer or execute the test binaries produced by the test projects.

Notes
- Some advanced patterns are intentionally simplified for C++17 compatibility; if you move to C++20 or later, consider using `constexpr` on lambdas explicitly and more ergonomic recursive constexpr patterns.
- The project aims to be educational; adapt the patterns to production code as appropriate and prefer clearer constexpr functions when complexity grows.

License
- Add your preferred license information here (e.g., MIT).