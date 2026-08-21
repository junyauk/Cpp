#include <iostream>
#include "classicthreadpipeline.h"

namespace Ex02_ThreadPool_WorkTimer
{
	ClassicThreadPipeline::ClassicThreadPipeline()
		: m_processedTasks(0), m_processedBytes(0)
	{
		const unsigned int numThreads = std::thread::hardware_concurrency();
		for (unsigned int i = 0; i < numThreads; ++i)
		{
			m_workerThreads.emplace_back([this](std::stop_token st) {WorkerThread(st); });
		}
	}
	ClassicThreadPipeline::~ClassicThreadPipeline()
	{
		Stop();
	}
	void ClassicThreadPipeline::SubmitTask(const TaskData& task)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_tasks.push(task);
		m_cv.notify_one();
	}
	void ClassicThreadPipeline::StartPeriodicMetrics(uint32_t intervalMs)
	{
		m_metricsThread = std::jthread([this, intervalMs](std::stop_token st) { MetricsThread(st, intervalMs); });
	}
	void ClassicThreadPipeline::Stop()
	{
		// Request stop for all worker threads and the metrics thread
		for (auto& thread : m_workerThreads)
		{
			thread.request_stop();
		}
		m_metricsThread.request_stop();

		// Notify all threads to wake up and check for stop requests
		m_cv.notify_all();

		// Join all worker threads and the metrics thread
		for (auto& thread : m_workerThreads)
		{
			if (thread.joinable())
			{
				thread.join();
			}
		}
		if (m_metricsThread.joinable())
		{
			m_metricsThread.join();
		}
	}

	uint64_t ClassicThreadPipeline::GetProcessedCount() const
	{
		return m_processedTasks.load();
	}

	void ClassicThreadPipeline::WorkerThread(std::stop_token st)
	{
		while (!st.stop_requested()	// Keep processing tasks until stop is requested
			|| !m_tasks.empty())	// Also process any remaining tasks in the queue
		{
			TaskData task;
			{
				std::unique_lock<std::mutex> lock(m_mutex);
				m_cv.wait(lock, [this, &st] { return !m_tasks.empty() || st.stop_requested(); });
				if (st.stop_requested() && m_tasks.empty())
				{
					return;
				}
				task = m_tasks.front();
				m_tasks.pop();
			}
			task.isProcessed = true;
			m_processedTasks.fetch_add(1);
			m_processedBytes.fetch_add(task.payload.size());
		}
	}

	void  ClassicThreadPipeline::MetricsThread(std::stop_token st, uint32_t intervalMs)
	{

		while (!st.stop_requested())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(intervalMs));
			if (st.stop_requested())
			{
				return;
			}
			uint64_t processedTasks = m_processedTasks.load();
			uint64_t processedBytes = m_processedBytes.load();
			// Doing something with the metrics, e.g., logging or printing
			std::cout << "Processed tasks: " << processedTasks << ", Processed bytes: " << processedBytes << std::endl;
		}
	}
}
