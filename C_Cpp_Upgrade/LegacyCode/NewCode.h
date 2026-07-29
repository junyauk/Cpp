#pragma once
#ifndef NEWCODE_H
#define NEWCODE_H

#include <stddef.h> // for size_t
#ifdef __cplusplus
extern "C" {
#endif

	// New C-style wrapper for array_sum_c implementation
	long cpp_wrapper_sum(const int* array, size_t count);

	// New C-style wrapper for array_double_and_copy implementation
	int* cpp_wrapper_double_and_copy(const int* source_array, size_t count);

	// New C-style wrapper for array_find_first implementation
	size_t cpp_wrapper_find_first(const int* array, size_t count, int target);

	// New C-style wrapper for array_sort_c implementation
	int cpp_wrapper_sort(void* base, size_t count, size_t size,
		int (*compar)(const void*, const void*));

	// New C-style wrapper for LoggerContext creation
	typedef struct LoggerContext_t LoggerContext_t; // defined in LegacyCode.cpp
	LoggerContext_t* cpp_wrapper_logger_create();
	int cpp_wrapper_logger_write(LoggerContext_t* ctx, const char* message);
	void cpp_wrapper_logger_destroy(LoggerContext_t* ctx);

#ifdef __cplusplus
}
#endif


#endif // !NEWCODE_H
