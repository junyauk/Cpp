#include <thread>
#include <iostream>
#include "modernthreadpoolpipeline.h"
#include "../Ex01_SRWLock_CondVar/srwlockwrapper.h"

using namespace Ex01_SRWLock_CondVar;

namespace Ex02_ThreadPool_WorkTimer
{
	ModernThreadPoolPipeline::ModernThreadPoolPipeline()
		: m_processedTasks(0), 
		m_processedBytes(0)
	{
		// Initialize the SRW lock
		InitializeSRWLock(&m_lock);

		m_pool.Initialize(1, std::thread::hardware_concurrency());
		m_pool.SetWork(WorkerCallback, this);
	}

	ModernThreadPoolPipeline::~ModernThreadPoolPipeline()
	{
		Stop();
	}

	void ModernThreadPoolPipeline::Stop()
	{
		m_pool.Stop();
	}

	uint64_t ModernThreadPoolPipeline::GetProcessedCount() const
	{
		return m_processedTasks.load();
	}

	void ModernThreadPoolPipeline::SubmitTask(const TaskData& task)
	{
		// Add the task to the queue in a thread-safe manner
		{
			SrwLockExclusive lock(m_lock);
			m_tasks.push(task);
		}
		// Submit work to the thread pool to process the task
		m_pool.SubmitWork();
	}

	void ModernThreadPoolPipeline::StartPeriodicMetrics(uint32_t intervalMs)
	{
		if (m_intervalMs == intervalMs)
		{
			return; // No need to change the interval if it's the same as the current one
		}
		m_intervalMs = intervalMs;
		m_pool.StartTimer(&MetricsCallback, this, intervalMs);
	}

	// Worker callback function for processing tasks
	// This function is called by the thread pool when a work item is submitted
	// It processes a single task from the queue and updates the processed task and byte counts
	// The function uses an SRW lock to protect access to the task queue
	void ModernThreadPoolPipeline::WorkerCallback(PTP_CALLBACK_INSTANCE Instance, PVOID Context, PTP_WORK Work)
	{
		// Process a single task from the queue
		ModernThreadPoolPipeline* pipeline = static_cast<ModernThreadPoolPipeline*>(Context);
		TaskData task;
		{
			// Use SRW lock to protect access to the task queue
			SrwLockExclusive lock(pipeline->m_lock);
			if (pipeline->m_tasks.empty())
			{
				// No tasks to process, return early
				return;
			}
			task = pipeline->m_tasks.front();
			pipeline->m_tasks.pop();
		}
		pipeline->m_processedTasks++;
		pipeline->m_processedBytes += task.payload.size();
	}

	// Metrics callback function for reporting processed task and byte counts
	// This function is called by the thread pool timer at the specified interval
	// It prints the current counts of processed tasks and bytes to the console
	// The function uses atomic variables to safely read the counts without locking
	// The function is static and takes a pointer to the ModernThreadPoolPipeline instance as context
	// The function is called by the thread pool timer, so it must be static and use the context pointer to access the instance
	void ModernThreadPoolPipeline::MetricsCallback(PTP_CALLBACK_INSTANCE Instance, PVOID Context, PTP_TIMER Timer)
	{
		// Use the context pointer to access the ModernThreadPoolPipeline instance
		ModernThreadPoolPipeline* pipeline = static_cast<ModernThreadPoolPipeline*>(Context);
		// Use atomic variables to safely read the counts without locking
		uint64_t processedTasks = pipeline->m_processedTasks.load();
		uint64_t processedBytes = pipeline->m_processedBytes.load();

		// Doing something with the metrics, e.g., logging or printing
		std::cout << "Processed tasks: " << processedTasks << ", Processed bytes: " << processedBytes << std::endl;
	}
}

