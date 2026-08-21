#pragma once
#include <Windows.h>
#include <queue>
#include "ipipeline.h"
#include "threadpool.h"

// Use Win32APIs instead of C++ STL to implement a thread pool. 
// - CreateThreadpoolWork
// - SubmitThreadpoolWork
// - CreateThreadpoolTimer
// - SRWLock
// The thread pool should be able to process tasks concurrently 
// and provide metrics on the number of processed tasks and bytes.

namespace Ex02_ThreadPool_WorkTimer
{
	class ModernThreadPoolPipeline : public IPipeline
	{
	public:
		ModernThreadPoolPipeline();
		~ModernThreadPoolPipeline();
		void SubmitTask(const TaskData& task) override;
		void StartPeriodicMetrics(uint32_t intervalMs) override;
		void Stop() override;
		uint64_t GetProcessedCount() const override;
	private:
		static void CALLBACK WorkerCallback(PTP_CALLBACK_INSTANCE Instance, PVOID Context, PTP_WORK Work);
		static void CALLBACK MetricsCallback(PTP_CALLBACK_INSTANCE Instance, PVOID Context, PTP_TIMER Timer);
		std::atomic<uint64_t> m_processedTasks;
		std::atomic<uint64_t> m_processedBytes;
		SRWLOCK m_lock;
		std::queue<TaskData> m_tasks;
		ThreadPool m_pool;
		uint32_t m_intervalMs = 0;
	};
}
