# C_Cpp_Upgrade

This solution contains sample code demonstrating how to modernize and wrap legacy C code using C++ (targeting C++14). It is intended as a personal learning/reference repository.

## Detected projects
- `LegacyCode` — Legacy C API with C++ wrapper implementations
  - Key files: `LegacyCode.c`, `LegacyCode.h`, `NewCode.cpp`, `NewCode.h`

## Purpose
- Show practical patterns for:
  - Wrapping C APIs with safer C++ implementations
  - Memory ownership and bridging conventions between C and C++
  - Minimal logger/context pattern across C/C++

## Requirements
- Windows 10/11
- Visual Studio 2022 (C++ workload)
- CMake (optional)
- C++14 for C++ source files

## Build (Visual Studio 2022)
1. Open the solution/project in Visual Studio 2022.
2. Select configuration (Debug/Release) and platform.
3. Build the solution.

## Build (CMake)
    mkdir build
    cd build
    cmake .. -G "Visual Studio 17 2022"
    cmake --build . --config Release

## NuGet / External Packages
- No NuGet packages detected in this solution. Only standard C/C++ libraries are used.

## Usage (summary)
`LegacyCode` exposes C functions; many delegate to C++ implementations in `NewCode.*`.

Main APIs:
- `long array_sum_c(const int* array, size_t count);`
- `int* array_double_and_copy(const int* source_array, size_t count);` — caller must free with `free()`.
- `size_t array_find_first(const int* array, size_t count, int target);`
- `int array_sort_c(void* base, size_t count, size_t size, int (*compar)(const void*, const void*));`
- Logger: `LoggerContext_t* logger_create(); int logger_write(LoggerContext_t* ctx, const char* message); void logger_destroy(LoggerContext_t* ctx);`

Example (C):
    #include "LegacyCode.h"
    #include <stdlib.h>

    int main(void)
    {
        int arr[] = {1,2,3,4};
        long s = array_sum_c(arr, 4);

        int* doubled = array_double_and_copy(arr, 4);
        if (doubled) {
            // use doubled...
            free(doubled); // important
        }

        return 0;
    }

## Contributing
- This repository is for personal learning. If you modify code, ensure it builds locally with Visual Studio 2022 and include brief notes in your changes.

## License
- No license specified for sample learning code. Add a LICENSE file if you plan to publish with specific terms.