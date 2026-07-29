#include "pch.h"
#include "NewCode.h"

#include <numeric>		// forstd::accumulate
#include <algorithm>	// for std::find
#include <vector>		// for std::vector
#include <iterator>		// for std::begin, std::end
#include <stdlib.h>		// for malloc, free
#include <iostream>		// for debugging

// Scenario 1: Internal C++ Implementation: Array Sum
long cpp_wrapper_sum(const int* array, size_t count)
{
	if (array == nullptr || count == 0)
	{
		return 0L;
	}

	return std::accumulate(array, array + count, 0L);
}


// Scenario 2: Internal C++ Implementation: Array Double and Copy
int* cpp_wrapper_double_and_copy(const int* source_array, size_t count)
{
	// 1. C-style input varidation
	if (source_array == nullptr || count == 0)
	{
		return nullptr;
	}
	
	// 2. Use std::vector for intermediate storage and processing
	std::vector<int> temp_result;
	for (auto i = 0; i < count; ++i)
	{
		temp_result.push_back(source_array[i] * 2);
	}

	// 3. Allocate C-style array using malloc
	size_t total_bytes = count * sizeof(int);
	int* c_raw_array = (int*)malloc(total_bytes);
	if (c_raw_array == nullptr)
	{
		return nullptr; // Memory allocation failed
	}
	// 4. Copy data from std::vector to C-style array
	for (size_t i = 0; i < count; ++i)
	{
		c_raw_array[i] = temp_result[i];
	}
	return c_raw_array;
}

// Scenario 3: Internal C++ Implementation: Array Find First
size_t cpp_wrapper_find_first(const int* array, size_t count, int target)
{
	// 1. C - style input varidation
	if (array == nullptr || count == 0)
	{
		return count; // Not found
	}

	const int* end_ptr = array + count;
	const int* found_ptr = std::find(array, end_ptr, target);
	if (found_ptr == end_ptr)
	{
		return count; // Not found
	}
	return std::distance(array, found_ptr);
}

// Scenario 4: Sort Wrapper
int cpp_wrapper_sort(void* base, size_t count, size_t size,
	int (*compar)(const void*, const void*))
{
	// 1. C-style input validation
	if (base == nullptr || count == 0 || size == 0 || compar == nullptr)
	{
		return -1; // Invalid input
	}
	int* begin = static_cast<int*>(base);
	int* end = begin + count;
	try
	{
		std::sort(begin, end,
			[compar](const int& a, const int& b) -> bool
			{
				return compar(&a, &b) < 0;
			});
	}
	catch (...)
	{
		return -1; // Sorting failed
	}
	return 0; // Success
}

// Scenario 5: Logger Context Creation

class CppLoggerContext
{
private:
	int message_count;
public:
	CppLoggerContext()
	{
		std::cout << "[CppLogger] Context initialized." << std::endl;
		// example:
		// Opening file, connecting to server, etc.
	}

	~CppLoggerContext()
	{
		std::cout << "[CppLogger] Context destroyed automatically. Total messages: " << message_count << std::endl;
		// example:
		// Closing file, disconnecting from server, etc.
	}

	int write(const char* message)
	{
		if (message == nullptr)
		{
			return -1; // Invalid message
		}
		++message_count;
		std::cout << "[CppLogger #" << message_count << "] " << message << std::endl;
		return 0; // Success
	}
};

LoggerContext_t* cpp_wrapper_logger_create()
{
	try
	{
		return reinterpret_cast<LoggerContext_t*>(new CppLoggerContext());
	}
	catch (...)
	{
		return nullptr;
	}
}

int cpp_wrapper_logger_write(LoggerContext_t* ctx, const char* message)
{
	if (ctx == nullptr)
	{
		return -1; // Invalid context
	}
	CppLoggerContext* cpp_ctx = reinterpret_cast<CppLoggerContext*>(ctx);
	return cpp_ctx->write(message);
}

void cpp_wrapper_logger_destroy(LoggerContext_t* ctx)
{
	if (ctx != nullptr)
	{
		CppLoggerContext* cpp_ctx = reinterpret_cast<CppLoggerContext*>(ctx);
		delete cpp_ctx; // Automatically calls destructor
	}
}

