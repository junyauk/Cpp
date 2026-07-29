# 05_Any

This project demonstrates practical patterns and trade‑offs when using `std::any` (C++17). It includes both basic, safe-access idioms and advanced examples that highlight copy vs. move costs when storing heterogeneous payloads.

Overview (expanded)
- Purpose and common uses
  - `std::any` is useful for storing heterogeneous values in a single container or configuration map when compile‑time type knowledge is limited or dynamic behavior is required.
  - This project shows how to use `std::any` for dynamic configuration, plugin-style value passing, and temporary storage of differently typed payloads.
- Safety patterns
  - Prefer safe access wrappers that return `std::optional<T>` rather than calling `std::any_cast<T>()` directly; this avoids exceptions on type mismatch and makes calling code explicit about handling absence.
  - Use the pointer form `std::any_cast<T>(&a)` for non‑throwing checks when you need to inspect or conditionally use a stored value.
- Type inspection and portability
  - Use `value.type()` and compare against `typeid(T)` for runtime type checks. Note that `type().name()` is implementation‑defined; avoid relying on its textual form for logic.
- Performance and move semantics
  - Storing large objects in `std::any` may imply copies. When ownership transfer is intended, move the stored object out using `std::any_cast<T&&>(std::move(a))` to avoid extra copies where supported.
  - The project includes `BigPayload` examples that implement copy and move constructors to illustrate observable differences.
- Error handling and API design
  - Wrap `std::any` usage behind small, well‑documented accessor functions to centralize type checks and conversions.
  - Document expected types for each key in a dynamic config map and prefer typed accessor helpers to reduce runtime errors.
- Testing and validation
  - Unit tests exercise safe vs unsafe retrieval, type detection, and move semantics expectations.
  - Tests demonstrate correct behavior for matching/non‑matching types and validate that moved values leave the source empty when appropriate.

Files
- `Any_Basic.h` / `Any_Basic.cpp` — basic dynamic-config examples and safe/unsafe access patterns.
- `Any_Advance.h` / `Any_Advance.cpp` — advanced examples for type inspection and move semantics with `std::any`.
- `05_AnyTest/AnyTest.cpp` — Google Test unit tests validating expected behaviors.

Requirements
- Windows 10/11
- Visual Studio 2022
- MSVC with C++17 support (ISO C++17)
- Google Test for running the test project (if desired)

Notes
- This project is educational: adopt the demonstrated patterns selectively and prefer stronger typed alternatives (e.g., `std::variant`) when union of known types is acceptable.
- Add license information as needed (e.g., MIT).
