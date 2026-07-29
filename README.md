# Cpp Learning Archive

This repository is a comprehensive collection of exercises, examples, and study
projects created while learning modern C++ across multiple versions (C++17,
C++20, and beyond).  
It serves both as a learning archive and a practical reference for revisiting
language features, syntax, idioms, and best practices.

Each folder focuses on specific C++ features or combined techniques, allowing
me to quickly recall how particular functionalities are used in real code.
The repository also acts as a portfolio demonstrating hands-on experience with
modern C++ design principles, testing practices, and feature exploration.

---

## Purpose

This repository is intended to:

- Document my learning process across C++17, C++20, and Modern C++  
- Provide a personal reference for recalling feature usage and best practices  
- Explore individual language features through focused exercises  
- Practice real-world development techniques using combined feature examples  
- Demonstrate practical understanding of modern C++ concepts, ranges,
  coroutines, modules, concurrency, constexpr, and more  
- Serve as a portfolio showcasing structured, test-driven C++ learning

---

## Repository Structure

### C++17Features
Focused exercises covering individual C++17 features such as:
- Structured bindings  
- If/Switch initialization  
- `std::optional`, `std::variant`, `std::any`  
- `std::filesystem`  
- Constexpr lambda  
- Fold expressions  
- Template argument deduction  
- Non-type template parameters  
- Inline variables  
- Parallel STL  
- Type traits & metaprogramming  

Each feature includes a dedicated test project.

---

### C++20Exercise
Practical exercises combining multiple C++20 features:
- Concepts + ranges  
- Coroutine generator  
- Async coroutine task  

These projects focus on real-world usage rather than isolated feature demos.

---

### C++20Features
Feature-by-feature exploration of C++20:
- Concepts  
- Modules (FinancialModule, ModulesApp, ModulesTest)  
- Ranges  
- Coroutines  
- Concurrency (`jthread`, `stop_token`, atomic wait)  
- `std::format`  
- Three-way comparison (`<=>`)  
- Designated initializers  
- Advanced constexpr  
- Sync streams  

This folder provides a near-complete coverage of major C++20 additions.

---

### Cpp17Examples
Practical examples demonstrating how C++17 features are used in real-world
scenarios:
- Structured bindings  
- Optional  
- CTAD  
- String view  
- Lambda improvements  
- Map/Set usage  
- Language feature demonstrations  

More practical and applied than the C++17Features folder.

---

### Cpp20Examples
Practical examples of C++20 features:
- Concepts basics  
- Ranges & views  
- `std::format`  
- `std::span`  
- Three-way comparison  
- `jthread` + `stop_token`  
- `std::source_location`  
- Advanced constexpr  
- Coroutine basics  

Includes shared test utilities for consistent testing.

---

### C_Cpp_Upgrade
Exercises converting legacy C-style code into modern C++ using:
- RAII  
- Smart pointers  
- STL  
- OOP principles  

Demonstrates understanding of safe memory management and modern design.

---

### ModernCpp_Mastery
Comprehensive Modern C++ practice including:
- Benchmarks  
- Combined exercises  
- Test suites  

This folder focuses on practical, real-world Modern C++ usage.

---

### ModuleExample
Practical multi-project examples demonstrating C++20 Modules:
- Caller modules  
- Legacy interop  
- MiniModules  
- Full module-based architecture  
- Module test projects  

Shows understanding of module structure and integration.

## Topics Covered

- Modern C++ design (RAII, smart pointers, move semantics, constexpr)
- C++17 features (optional, variant, any, filesystem, fold expressions)
- C++20 features (concepts, ranges, coroutines, modules, concurrency)
- Testing practices (feature tests, utility tests, TDD-style structure)
- Performance benchmarking
- Migration from C to C++ (memory safety, abstraction, OOP)

---

## Build Instructions
### Using Visual Studio
Open the `.sln` file in Visual Studio and build normally.

---

## How to Use This Repository as a Reference

- Browse feature folders to recall how specific C++17/C++20 features work  
- Use example folders to see practical usage patterns  
- Check test projects to understand expected behavior  
- Review ModernCpp_Mastery for real-world design and performance techniques  
- Explore ModuleExample to understand C++20 module structure  

---

## Future Work

- Add C++23 feature exercises  
- Expand coroutine examples  
- Add more module-based architecture samples  
- Extend benchmarking suite  
- Add documentation and diagrams for complex examples  

---

## License

MIT

