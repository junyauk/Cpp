#pragma once
#include <vector>
#include <algorithm> 
#include <execution>	// Required for execution policies (par, seq, par_unseq)
#include <chrono>		// For timing utilities
#include <iostream>


namespace PARALLELSTL_Basic
{
	class ParallelSTL_Basic
	{
	public:
		// Helper: Generates a large vector for performance testing
		static std::vector<long> generateLargeVector(size_t size);

		// 1. Parallel std::sort
		// Sorts the vector using the parallel policy (std::execution::par) and returns the duration.
		double sortParallel(std::vector<long>& vec);

		// 2. Sequential std::sort (Baseline)
		// Sorts the vector using the sequential policy (std::execution::seq) or default sort.
		double sortSequential(std::vector<long>& vec);

		// 3. Parallel std::for_each
		// Applies a calculation to every element using the parallel policy.
		void processInParallel(std::vector<long>& vec) const;

		// 4. Sequential std::for_each (Baseline)
		// Applies the same calculation sequentially.
		void processSequentially(std::vector<long>& vec) const;
	};

	// CPU-intensive dummy calculation function
	void complex_calc(long& val);
}
