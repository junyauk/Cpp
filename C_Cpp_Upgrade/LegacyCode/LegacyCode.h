#ifndef LEGACYCODE_H
#define LEGACYCODE_H

#include <stddef.h> // for size_t
#include <stdlib.h> // for malloc/free

// Even though this is a C header, we use extern "C" to allow inclusion in C++ code.
#ifdef __cplusplus
extern "C" {
#endif

// Scenario 1 : Data structure (Array Sum)
long array_sum_c(const int* array, size_t count);

// Scenario 2: Memory Management (Array Copy)
// The caller is responsible for freeing the returned pointer using free().
int* array_double_and_copy(const int* source_array, size_t count);

// Scenario 3: Data Search (Linear Search)
// Returns the index or 'count' if not found.
size_t array_find_first(const int* array, size_t count, int target);

// Scenario 4: Generic Array Sort (Using Function Pointer for Comparison)
// Returns 0 on success, non-zero on failure.
int array_sort_c(void* base, size_t count, size_t size,
    int (*compar)(const void*, const void*));

// Scenario 5: Logger Context Creation
typedef struct LoggerContext_t LoggerContext_t;
LoggerContext_t* logger_create();
int logger_write(LoggerContext_t* ctx, const char* message);
void logger_destroy(LoggerContext_t* ctx);

#ifdef __cplusplus
}
#endif

#endif // LEGACYCODE_H
