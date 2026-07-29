# 08_FoldExpressionsTest

This test project contains Google Test unit tests for the `08_FoldExpressions` examples. Tests validate correctness and edge cases of fold expression usage: arithmetic aggregation, mixed-type folding, stream concatenation semantics, boolean folds, and empty-pack behavior.

Contents
- `FoldExpressionsTest.cpp` — Tests include:
  - `sumAll` with integer and mixed-type arguments (validates result type and numeric aggregation).
  - `concatnate` (checks presence of concatenated parts and expected separators).
  - `allTrue` boolean fold tests (all true, one false, and empty pack behavior).
- Additional tests (if present) validate advanced sequencing and constexpr fold helpers.

Requirements
- Visual Studio 2022
- MSVC configured for ISO C++17
- Google Test configured in the solution (vcpkg, submodule, or vendor)

Build & Run Tests
- Build the solution in Visual Studio (Right‑click solution → `Build Solution`).  
- Run tests from Test Explorer (Test → Test Explorer) or execute the test binary:
  Example: `.\08_FoldExpressionsTest\Debug\08_FoldExpressionsTest.exe`

Expected behavior summary
- Numeric folds return correct aggregated values and proper type promotion for mixed arithmetic.
- Stream concatenation includes `init` and all subsequent arguments in order with separators.
- Logical folds obey short-circuit semantics where applicable and define correct results for empty packs (`allTrue()` -> `true`).

Notes
- If tests fail, verify that the projects compile with ISO C++17 and that Google Test is correctly configured.
- Add license or contributing references in the parent project README if desired.