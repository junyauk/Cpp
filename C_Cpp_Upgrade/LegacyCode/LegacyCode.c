// Original implementation of all APIs using pure C language.
#include <stdio.h>	// for simple I/O (debugging)
#include <stdlib.h>	// for malloc, free, qsort
#include <string.h>	// for strlen
#include "LegacyCode.h"
#include "NewCode.h"

long array_sum_c(const int* array, size_t count)
{
#if 1
	// Calling the new C++ wrapper implementation
	return cpp_wrapper_sum(array, count);
#else
	// C-style implementation
	long sum = 0;
	if (array == NULL || count == 0)
	{
		return 0;
	}
	for (size_t i = 0; i < count; ++i)
	{
		sum += array[i];
	}
	return sum;
#endif
}

// --- Scenario 2: Memory Management (Array Copy) ---
int* array_double_and_copy(const int* source_array, size_t count)
{
#if 1
	// Calling the new C++ wrapper implementation
	return cpp_wrapper_double_and_copy(source_array, count);
#else
	// C-style implementation
	if (source_array == NULL || count == 0)
	{
		return NULL;
	}

	size_t total_bytes = count * sizeof(int);
	int* c_raw_array = (int*)malloc(total_bytes);
	if (c_raw_array == NULL)
	{
		return NULL; // Memory allocation failed
	}

	for (size_t i = 0; i < count; ++i)
	{
		c_raw_array[i] = source_array[i] * 2;
	}

	return c_raw_array;
#endif
}

// --- Scenario 3: Data Search (Linear Search) ---
size_t array_find_first(const int* array, size_t count, int target)
{
#if 1
	// Calling the new C++ wrapper implementation
	return cpp_wrapper_find_first(array, count, target);
#else
	// C-style linear search implementation
	if (array == NULL || count == 0)
	{
		return count; // Not found
	}
	for (size_t i = 0; i < count; ++i)
	{
		if (array[i] == target)
		{
			return i; // Found at index i
		}
	}
	return count; // Not found
#endif
}

// --- Scenario 4: Sort (qsort imitation) ---
// Note: This C implementation simply acts as a wrapper for the standard qsort function
// as reimplementing a generic quicksort in C is complex.
int array_sort_c(void* base, size_t count, size_t size,
	int (*compar)(const void*, const void*))
{
#if 1
	// Calling the new C++ wrapper implementation
	return cpp_wrapper_sort(base, count, size, compar);
#else
	if (base == NULL || count <=1 || size == 0 || compar == NULL)
	{
		// If already sorted or invalid input, treat as success or handle error
		return (count <=1)? 0 : -1;
	}

	// Use qsort from the C standard library
	qsort(base, count, size, compar);

	return 0; // Success
#endif
}

// --- Scenario 5: Logger Context Creation ---

// Simple LoggerContext structure that is only visible within this C file
struct LoggerContext_t
{
	int message_count;
};

// Creates and initializes a new LoggerContext
LoggerContext_t* logger_create()
{
#if 1
	// Calling the new C++ wrapper implementation
	return cpp_wrapper_logger_create();
#else
	// Allocate memory for LoggerContext
	LoggerContext_t* ctx = (LoggerContext_t*)malloc(sizeof(LoggerContext_t));
	if (ctx != NULL)
	{
		// Initialize context
		ctx->message_count = 0;
	}
	return ctx;
#endif
}

// Writes a log message using the LoggerContext
int logger_write(LoggerContext_t* ctx, const char* message)
{
#if 1
	// Calling the new C++ wrapper implementation
	return cpp_wrapper_logger_write(ctx, message);
#else
	if (ctx == NULL || message == NULL)
	{
		return -1; // Invalid input
	}
	// Simple logging to stdout
	printf("[Logger #%d] %s\n", ctx->message_count, message);
	return 0; // Success
#endif
}

// Destroys the LoggerContext and frees associated resources
void logger_destroy(LoggerContext_t* ctx)
{
#if 1
	// Calling the new C++ wrapper implementation
	cpp_wrapper_logger_destroy(ctx);
#else
	if (ctx != NULL)
	{
		printf("[Logger] Context destroyed. Total messages: %d\n", ctx->message_count);
		free(ctx);
	}
#endif
}
