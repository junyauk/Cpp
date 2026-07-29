#include "pch.h"
#include "framework.h"

#include <numeric>
#include <iostream>
#include "04_StdSpan.h"

namespace StdSpanSamples
{
	int Sum(std::span<const int> values)
	{
		return std::accumulate(values.begin(), values.end(), 0);
	}

	std::span<const int> GetSubspan(std::span<const int> values, size_t offset, size_t count)
	{
		return values.subspan(offset, count);
	}

	bool ContainsChar(std::span<const char> chars, char target)
	{
		return (std::find(chars.begin(), chars.end(), target) != chars.end());
	}

	int SumMatrix(std::span<const int> matrix)
	{
		return std::accumulate(matrix.begin(), matrix.end(), 0);
	}

	void PrintNumbers(std::span<const int> numbers)
	{
		for (auto n : numbers)
		{
			std::cout << n << " ";
		}
		std::cout << std::endl;
	}

	void FillBuffer(std::span<int> buf, int value)
	{
		for (auto& n : buf)
		{
			n = value;
		}
	}

	void PrintMatrix(std::span<int, 9> matrix)
	{
		for (int i = 0; i < 9; ++i)
		{
			std::cout << matrix[i] << ((i % 3 == 2) ? "\n" : " ");
		}
	}

}


