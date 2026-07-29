# 09_TemplateDeduction

This project demonstrates C++17 template argument deduction (CTAD) and user-defined deduction guides. It provides focused examples showing how the compiler deduces template parameters from constructor arguments, how to write deduction guides for custom classes, and practical patterns for applying CTAD in user code.

Overview
- Purpose and common scenarios
  - Explain and demonstrate Class Template Argument Deduction (CTAD) introduced in C++17.
  - Show how CTAD simplifies code by letting the compiler infer template arguments from constructor calls.
  - Provide examples of user-defined deduction guides to control and extend CTAD behavior for custom templates.
  - Compare CTAD usage in small utility types and more complex user-defined containers.

- Key concepts demonstrated
  - Implicit CTAD: creating template instances without specifying template arguments (e.g., `SimpleWrapper wrapper(val);`).
  - Deduction guides: writing explicit guides (e.g., `CountedBuffer(T*, size_t) -> CountedBuffer<T>`) that map constructor parameter types to class template parameters.
  - CTAD for user containers: enabling initializer-list, pointer+size, and iterator-pair deduction for `MyVector`.
  - Interaction with standard library CTAD (e.g., `std::pair`, `std::vector`) and how to design custom types to follow similar patterns.

Files
- `TemplateDeduction_Basic.h` / `TemplateDeduction_Basic.cpp`
  - `SimpleWrapper<T>`: simple wrapper that benefits from implicit CTAD.
  - `CountedBuffer<T>`: demonstrates a manual deduction guide for pointer+size constructors.
  - `CTAD_Basic` helper class with example functions that instantiate templates via CTAD.
- `CTAD_Advance.h`
  - `MyVector<T>`: user-defined container with multiple constructors and corresponding deduction guides:
    - initializer-list guide,
    - pointer+size guide,
    - iterator-pair guide (deduces value_type from iterator_traits).
  - Helper methods showing CTAD use with standard containers and nested types.
- `09_TemplateDeductionTest/TemplateDeductionTest.cpp`
  - Unit tests that validate CTAD behavior and deduction-guides usage.

Requirements
- Windows 10/11
- Visual Studio 2022
- MSVC with C++17 support (ISO C++17)
- Google Test for the test project

Build
1. Open the solution or project folder in Visual Studio 2022.  
2. Ensure the C++ language standard is set to ISO C++17:
   Project Properties → `C/C++` → `Language` → `C++ Language Standard` → `ISO C++17`.  
3. Build the solution (Right‑click solution → `Build Solution`).

Notes
- CTAD improves readability but be explicit when clarity is desirable—use deduction guides to make inferred types obvious.
- When providing deduction guides, ensure they cover the constructor forms you intend to allow and avoid ambiguous guides.
- This project is educational: adapt patterns to your codebase and prefer explicit template arguments when the inferred type may be surprising.
- Add license information as needed (e.g., MIT).