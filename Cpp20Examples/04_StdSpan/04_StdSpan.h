#pragma once
#include <span>
#include <vector>
#include <string>
#include <array>
#include <cstddef>

namespace StdSpanSamples
{
	int Sum(std::span<const int> values);
	std::span<const int> GetSubspan(std::span<const int> values, size_t offset, size_t count);
	bool ContainsChar(std::span<const char> chars, char target);
	int SumMatrix(std::span<const int> matrix);
	void PrintNumbers(std::span<const int> numbers);
	void FillBuffer(std::span<int> buf, int value);
	void PrintMatrix(std::span<int, 9> matrix);
}


