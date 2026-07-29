#pragma once
#include <thread>
#include <span>
#include "job.h"
#include "work_stealing_queue.h"
#include "simple_logger.h"

using namespace SimpleLogger;

namespace Ex02_JobSystem
{
	inline constexpr size_t INVALID_WORKER_ID = static_cast<size_t>(-1);
	inline thread_local size_t t_currentWorkerId = INVALID_WORKER_ID;

	template<typename T>
	class WorkerThread
	{
	private:
		size_t m_id;
		inline static std::atomic<size_t> nextId = 0;
		std::span<std::unique_ptr<WorkerThread<T>>> m_workerThreads; // Caller should guarantee the lifetime.
		WorkStealingQueue<T> m_queue;
		std::jthread m_thread;


		void runProcessLoop(std::stop_token token)
		{
			LOG(INFO) << "WorkerThread::runProcessLooop(" << m_id << ") ->";

			Ex02_JobSystem::t_currentWorkerId = m_id;

			while (true)
			{
				if (token.stop_requested() && m_queue.empty())
				{
					break;
				}
				std::optional<T> job = m_queue.pop();
				if (job.has_value())
				{
					LOG(INFO) << " " << m_id << "       popped job";
					job.value()();
				}
				else
				{
					LOG(INFO) << " " << m_id << "       m_queue is empty";

					bool invoked = false;
					uint32_t startIndex = (static_cast<uint32_t>(m_id) + 1) % m_workerThreads.size();

					for (uint32_t i = 0; i < m_workerThreads.size(); ++i)
					{
						uint32_t targetIndex = (startIndex + i) % m_workerThreads.size();
						std::unique_ptr<WorkerThread<T>>& w = m_workerThreads[targetIndex];
						if (w.get() != this)
						{
							std::optional<T> j = w->steal();
							if (j.has_value())
							{
								LOG(INFO) << " " << m_id << "       stealed job";
								j.value()();
								invoked = true;
								break;
							}
						}
					}
					if (!invoked)
					{
						std::this_thread::yield();
					}
				}
			}
			LOG(INFO) << "WorkerThread::runProcessLooop(" << m_id << ") <-";
		}

	public:
		WorkerThread() : m_id(nextId++) {}

		void setSiblings(std::span<std::unique_ptr<WorkerThread<T>>> workers)
		{
			m_workerThreads = workers;
		}

		bool start()
		{
			LOG(INFO) << "WorkerThread::start(" << m_id << ") ->";
			if (m_thread.joinable() || m_workerThreads.empty())
			{
				LOG(INFO) << "WorkerThread::start(m_joinable or siblings are empty) <-";
				return false;
			}

//			m_thread = std::jthread(&WorkerThread::runProcessLoop, this);				// Directly pass
			m_thread = std::jthread([this](std::stop_token st) { runProcessLoop(st); });// Use lambda (it can add another params)
			LOG(INFO) << "WorkerThread::start(" << m_id << ") <-";
			return true;
		}
		void stop()
		{
			LOG(INFO) << "WorkerThread::stop(" << m_id << ") ->";

			m_thread.request_stop();
			LOG(INFO) << "WorkerThread::stop(" << m_id << ") <-";
		}

		void join()
		{
			LOG(INFO) << "WorkerThread::join(" << m_id << ") ->";
			if (m_thread.joinable())
			{
				m_thread.join();
			}
			LOG(INFO) << "WorkerThread::join(" << m_id << ") <-";
		}

		size_t getId() const
		{
			return m_id;
		}

		void push(T job)
		{
			LOG(INFO) << "WorkerThread::push(" << m_id << ") ->";
			m_queue.push(std::move(job));
			LOG(INFO) << "WorkerThread::push(" << m_id << ") <-";
		}

		std::optional<T> steal()
		{
			LOG(INFO) << "WorkerThread::steal(" << m_id << ")";
			return m_queue.steal();
		}
	};
}
