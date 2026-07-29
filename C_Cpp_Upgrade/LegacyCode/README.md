# LegacyCode

Legacy C APIs with thin C++14 wrapper implementations. This project demonstrates safe migration patterns from C to modern C++ while keeping a C-compatible surface.

## Files
- `LegacyCode.h` — public C header for the legacy API.
- `LegacyCode.c` — legacy C implementations that forward to C++ wrappers (toggleable via `#if` switches).
- `NewCode.h` — C-compatible declarations for the C++ wrapper functions.
- `NewCode.cpp` — C++14 implementations used by the legacy functions.

## API Overview
- `long array_sum_c(const int* array, size_t count);`
  - Returns sum of array elements. Handles `NULL` and zero-length gracefully.
- `int* array_double_and_copy(const int* source_array, size_t count);`
  - Returns a newly allocated array (caller must `free()` the returned pointer).
- `size_t array_find_first(const int* array, size_t count, int target);`
  - Returns index or `count` if not found.
- `int array_sort_c(void* base, size_t count, size_t size, int (*compar)(const void*, const void*));`
  - Sorts array; returns 0 on success.
- Logger:
  - `LoggerContext_t* logger_create();`
  - `int logger_write(LoggerContext_t* ctx, const char* message);`
  - `void logger_destroy(LoggerContext_t* ctx);`

## Memory & Ownership Notes
- Functions returning pointers allocate with C allocator conventions; the caller is responsible for `free()` when applicable.
- Logger context is opaque (`LoggerContext_t*`) and must be destroyed with `logger_destroy()`.

## Building
- Build as part of the solution using Visual Studio 2022.
- C++ files target C++14.

## Examples
C usage:
    #include "LegacyCode.h"
    #include <stdlib.h>

    int main(void)
    {
        int a[] = {10, 20, 30};
        long total = array_sum_c(a, 3);

        int* doubled = array_double_and_copy(a, 3);
        if (doubled) {
            // use doubled
            free(doubled);
        }

        return 0;
    }

C++ usage (calling C API):
    #include "LegacyCode.h"
    #include <vector>

    int main()
    {
        std::vector<int> v{3,1,2};
        array_sort_c(v.data(), v.size(), sizeof(int), [](const void* a, const void* b) {
            int ia = *(const int*)a;
            int ib = *(const int*)b;
            return (ia > ib) - (ia < ib);
        });
        return 0;
    }

## Notes
- You can experiment by switching the `#if` blocks in `LegacyCode.c` to use pure-C implementations instead of forwarding to C++ wrappers.# Go to repo root
Set-Location -Path "C:\Users\Junya\source\Cpp"

# Create directories if needed
New-Item -ItemType Directory -Force -Path ".\C_Cpp_Upgrade" | Out-Null
New-Item -ItemType Directory -Force -Path ".\C_Cpp_Upgrade\LegacyCode" | Out-Null

# Write files (UTF8)
@'
# C_Cpp_Upgrade

This solution contains sample code demonstrating how to modernize and wrap legacy C code using C++ (targeting C++14). It is intended as a personal learning/reference repository.

... (paste the root README content here exactly as provided above) ...
'@ | Out-File -FilePath ".\C_Cpp_Upgrade\README.md" -Encoding utf8

@'
# LegacyCode

Legacy C APIs with thin C++14 wrapper implementations. This project demonstrates safe migration patterns from C to modern C++ while keeping a C-compatible surface.

... (paste the LegacyCode README content here exactly as provided above) ...
'@ | Out-File -FilePath ".\C_Cpp_Upgrade\LegacyCode\README.md" -Encoding utf8

# Verify
Get-Content .\C_Cpp_Upgrade\README.md -TotalCount 10
Get-Content .\C_Cpp_Upgrade\LegacyCode\README.md -TotalCount 10

# Git add/commit/push
git add C_Cpp_Upgrade\README.md C_Cpp_Upgrade\LegacyCode\README.md
git commit -m "Add README files for solution and LegacyCode project"
git push origin main
