#pragma once
#include "taskdata.h"

namespace Ex02_ThreadPool_WorkTimer
{
	class IPipeline
	{
	public:
		virtual void SubmitTask(const TaskData& task) = 0;
		virtual void StartPeriodicMetrics(uint32_t intervalMs) = 0;
		virtual void Stop() = 0;
		virtual uint64_t GetProcessedCount() const = 0;
	};
}
