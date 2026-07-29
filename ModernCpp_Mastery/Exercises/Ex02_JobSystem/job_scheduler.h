#pragma once
#include <vector>
#include <memory>
#include <thread>
#include "simple_logger.h"
#include "job.h"
#include "worker_thread.h"

using namespace SimpleLogger;

namespace Ex02_JobSystem
{
	class JobScheduler
	{
	private:
		std::atomic<size_t> m_nextWorkerIndex = 0;
		uint8_t m_numThreads;
		std::vector<std::unique_ptr<WorkerThread<Job>>> m_workerThreads;


	public:
		JobScheduler(uint8_t numThreads = 0)
			: m_numThreads(numThreads ? numThreads : std::thread::hardware_concurrency())
		{
			for (uint8_t i = 0; i < m_numThreads; ++i)
			{
				m_workerThreads.push_back(std::make_unique<WorkerThread<Job>>());
			}
			for (uint8_t i = 0; i < m_numThreads; ++i)
			{
				m_workerThreads[i]->setSiblings(m_workerThreads);
			}
			for (uint8_t i = 0; i < m_numThreads; ++i)
			{
				m_workerThreads[i]->start();
			}
		}
		~JobScheduler()
		{
			stop();
			join();
		}

		template<typename F, typename... Args>
		requires JobCallable<F, Args...>
		void submit(F&& func, Args&&... args)
		{
			LOG(INFO) << "JobScheduler::submit() ->";
			if (Ex02_JobSystem::t_currentWorkerId == INVALID_WORKER_ID)
			{
				// .submit() was called from main thread.
				auto targetIndex = m_nextWorkerIndex.fetch_add(1, std::memory_order_relaxed) % m_workerThreads.size();
				std::unique_ptr<WorkerThread<Job>>& w = m_workerThreads[targetIndex];
				w->push(Job(std::forward<F>(func), std::forward<Args>(args)...));
			}
			else
			{
				m_workerThreads[Ex02_JobSystem::t_currentWorkerId]->push(Job(std::forward<F>(func), std::forward<Args>(args)...));
			}
			LOG(INFO) << "JobScheduler::submit() <-";
		}
		void stop()
		{
			LOG(INFO) << "JobScheduler::stop() ->";
			for (auto& w : m_workerThreads)
			{
				w->stop();
			}
			LOG(INFO) << "JobScheduler::stop() <-";
		}
		void join()
		{
			LOG(INFO) << "JobScheduler::join() ->";

			for (auto& w : m_workerThreads)
			{
				w->join();
			}
			LOG(INFO) << "JobScheduler::join() <-";
		}
	};
}
