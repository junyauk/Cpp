#include "pch.h"
#include "framework.h"
#include <random>
#include <cmath>
#include <numeric>
#include "ParallelSTL_Basic.h"

namespace PARALLELSTL_Basic
{
    // CPU-intensive dummy calculation function (assumes thread-safe operations on 'val')
    void complex_calc(long& val)
    {
        // Simple calculation to ensure CPU load
        // The value effectively returns to the original, but the computation takes time.
        val = static_cast<long>(std::pow(std::sqrt(static_cast<double>(val)), 2.0));
    }

	std::vector<long> ParallelSTL_Basic::generateLargeVector(size_t size)
	{
		std::vector<long> vec(size);
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<long> distrib(1, 10000000);

		for (auto i = 0; i < size; ++i)
		{
			vec[i] = distrib(gen);
		}
		return vec;
	}

	// 1. Parallel std::sort
	double ParallelSTL_Basic::sortParallel(std::vector<long>& vec)
	{
		auto start = std::chrono::high_resolution_clock::now();

		// Use std::execution::par for parallel execution
		std::sort(std::execution::par, vec.begin(), vec.end());

		auto end = std::chrono::high_resolution_clock::now();

		// Return duration in milliseconds
		std::chrono::duration<double, std::milli> duration = end - start;
		return duration.count();
	}

	// 2. Sequential std::sort (Baseline)
	double ParallelSTL_Basic::sortSequential(std::vector<long>& vec)
	{
		auto start = std::chrono::high_resolution_clock::now();

		// Default sequential execution
		std::sort(vec.begin(), vec.end());

		auto end = std::chrono::high_resolution_clock::now();

		// Return duration in milliseconds
		std::chrono::duration<double, std::milli> duration = end - start;
		return duration.count();
	}

	// 3. Parallel std::for_each
	void ParallelSTL_Basic::processInParallel(std::vector<long>& vec) const
	{
		// Use std::execution::par to apply complex_calc in parallel
		std::for_each(std::execution::par, vec.begin(), vec.end(), complex_calc);
	}

	// 4. Sequential std::for_each (Baseline)
	void ParallelSTL_Basic::processSequentially(std::vector<long>& vec) const
	{
		// Sequential execution
		std::for_each(vec.begin(), vec.end(), complex_calc);
	}
}
