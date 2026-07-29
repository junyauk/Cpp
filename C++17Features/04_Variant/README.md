# 04_Variant

This project demonstrates C++17 `std::variant` usage with basic and advanced patterns, including visitors, multi-variant visits, type-safe error handling, and `std::monostate`.

Overview
- Basic examples (`Variant_Basic`):
  - `DataValue = std::variant<int, double, std::string>` stored in a `std::vector`.
  - `addValue(T&&)` — adds values via perfect forwarding.
  - `getTypeAtIndex(size_t)` — inspects held type using `std::holds_alternative`.
  - `getIntAt(size_t)` — accesses value with `std::get<int>` (throws on mismatch).
  - `processAllValues()` — mutates values using `std::visit` and a functor.
  - `convertValueToString(size_t)` — converts any held value to `std::string` via `std::visit`.

- Advanced examples (`Variant_Advance`):
  - `processMultipleVariants(const VariantA&, const VariantB&)` — multi-variant visitation combining behaviors using the `overload` helper.
  - `calculateValue(double)` → `ResultType = std::variant<SuccessType, ErrorInfo>` — type-safe success/error return.
  - `checkResultForError(const ResultType&)` — safe inspection with `std::get_if`.
  - `checkStatus(const StatusVariant&)` — demonstrates `std::monostate` for explicit "empty/uninitialized" state.

Files
- `Variant_Basic.h` / `Variant_Basic.cpp` — core basic examples and the `ValueProcesser` visitor.
- `Variant_Advance.h` / `Variant_Advance.cpp` — advanced patterns, `overload` helper template, and monostate usage.
- `../04_VariantTest/` — unit tests for basic and advanced behaviors.

Requirements
- Windows 10/11
- Visual Studio 2022
- MSVC with C++17 support (ISO C++17)
- Google Test for running unit tests (if present)

Build
1. Open the solution or project folder in Visual Studio 2022.  
2. Ensure projects use ISO C++17: Project Properties → C/C++ → Language → C++ Language Standard → `ISO C++17`.  
3. Build the solution (Right-click solution → Build Solution).

Usage examples (conceptual)
- Use `std::visit` with an `overload` helper to handle multiple variant alternatives cleanly.
- Use `std::get_if` to check for error variant without throwing.
- Prefer `std::monostate` when you need an explicit "empty" alternative that is visitable.

Notes
- `overload` helper emulates the common visitor pattern for `std::visit`.
- `ResultType` demonstrates replacing ad-hoc error codes with type-safe variants containing either success or structured error info.
- Be careful with `std::get<T>`; it throws `std::bad_variant_access` on type mismatch — prefer `std::get_if` or `std::visit` for safer handling.

License
- Add your preferred license (e.g., MIT).
