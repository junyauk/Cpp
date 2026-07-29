# 13_TypeTraitsAndMetaprogrammingTest

This test project contains unit tests (Google Test) for the `13_TypeTraitsAndMetaprogramming` utilities. Tests verify compile‑time trait behavior, detection idiom outcomes, type‑list operations, and SFINAE/`constexpr if` based overload selection used throughout the examples.

Contents
- `TypeTraits_Basic` tests
  - Validate basic `std` trait aliases and helper wrappers (e.g. `is_same_v`, `is_integral_v`, remove/decay helpers).
- `TypeTraits_Advance` tests
  - Verify detection idiom utilities (`is_detected` / `detected_t` style), `is_callable` behavior, and correct SFINAE selection.
  - Validate type‑list utilities: counting, filtering and mapping operations implemented with variadic templates.
  - Confirm `constexpr if` branches and `static_assert` expectations where applicable.

Requirements
- Visual Studio 2022
- MSVC configured for C++17 (ISO C++17)
- Google Test integrated in the solution (vcpkg, submodule, or vendor)

Build
1. Open the solution in Visual Studio 2022.  
2. Ensure the test project and implementation target `ISO C++17`:
   Project Properties → `C/C++` → `Language` → `C++ Language Standard` → `ISO C++17`.  
3. Build the solution (Right‑click solution → `Build Solution`).

Run tests
- Run tests from Visual Studio Test Explorer (Test → Test Explorer).
- Or execute the produced test binary:
  Example: `.\13_TypeTraitsAndMetaprogrammingTest\Debug\13_TypeTraitsAndMetaprogrammingTest.exe`

Expected behavior
- Detection idiom correctly identifies presence/absence of members and expressions without hard errors.
- Trait combinators and alias templates produce expected compile‑time boolean results.
- Type‑list operations return correct sizes and filtered lists; `static_assert` checks compile‑time invariants used in tests pass.

Notes
- Tests include both runtime assertions and compile‑time checks (`static_assert`) where appropriate; compilation must succeed for the latter to validate.
- If tests fail, include compiler diagnostics and the exact MSVC/STL configuration when reporting issues.
- Add license or contributing references in the parent project README if desired.