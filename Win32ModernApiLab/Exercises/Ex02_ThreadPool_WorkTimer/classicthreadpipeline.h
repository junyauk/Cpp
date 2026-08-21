#pragma once
#include <mutex>
#include <queue>
#include <thread>
#include <vector>
#include <condition_variable>
#include "ipipeline.h"

namespace Ex02_ThreadPool_WorkTimer
{
	class ClassicThreadPipeline : public IPipeline
	{
	public:
		ClassicThreadPipeline();
		~ClassicThreadPipeline();
		void SubmitTask(const TaskData& task) override;
		void StartPeriodicMetrics(uint32_t intervalMs) override;
		void Stop() override;
		uint64_t GetProcessedCount() const override;
	private:
		void WorkerThread(std::stop_token st);
		void MetricsThread(std::stop_token st, uint32_t intervalMs);
		std::atomic<uint64_t> m_processedTasks;
		std::atomic<uint64_t> m_processedBytes;
		mutable std::mutex m_mutex;
		std::condition_variable m_cv;
		std::queue<TaskData> m_tasks;
		std::jthread m_metricsThread;
		std::vector<std::jthread> m_workerThreads;
	};
}
