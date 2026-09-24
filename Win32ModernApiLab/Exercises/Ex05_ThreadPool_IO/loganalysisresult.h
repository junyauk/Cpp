#pragma once
#include <chrono>
#include <atomic>

namespace Ex05_ThreadPool_IO
{
	struct LogAnalysisResult
	{
		uint64_t totalLines = 0;
		uint64_t errorCounts = 0;
		uint64_t totalBytes = 0;
		std::chrono::microseconds processingTime = std::chrono::microseconds(0);
	};
}
