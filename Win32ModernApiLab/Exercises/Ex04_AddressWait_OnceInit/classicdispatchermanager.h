#pragma once
#include <vector>
#include <mutex>
#include <queue>
#include <thread>
#include "classicevent.h"
#include "taskdata.h"

namespace Ex04_AddressWait_OnceInit
{
	class ClassicDispatcherManager
	{
	public:
		ClassicDispatcherManager()
			: m_event(false) // Only one thread is allowed
		{
			m_numThreads = std::thread::hardware_concurrency();
			for (size_t i = 0; i < m_numThreads; ++i)
			{
				m_threads.emplace_back([&](std::stop_token st) {WorkerThread(st); });
			}
		}

		~ClassicDispatcherManager()
		{
			if (!m_threads.empty())
			{
				Stop();
			}
		}

		static ClassicDispatcherManager* GetInstance()
		{
			static ClassicDispatcherManager instance;
			return &instance; // All threads will share this
		}

		void Push(TaskData data)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			m_queue.push(data);
			m_event.Set(); // Activate one of threads
		}
		bool Pop(TaskData* data)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			if (!m_queue.empty())
			{
				*data = m_queue.front();
				m_queue.pop();
				return true;
			}
			return false;
		}
		uint32_t Stop()
		{
			// Letting threads know stop requested
			for (auto& t : m_threads)
			{
				t.request_stop();
			}

			// Kick off one of threads after stop requested
			m_event.Set();

			for (auto& t : m_threads)
			{
				if (t.joinable())
				{
					t.join();
				}
			}
			m_threads.clear();

			return m_processedCount.load();
		}


		// Rule of five
		ClassicDispatcherManager(const ClassicDispatcherManager&) = delete;
		ClassicDispatcherManager(ClassicDispatcherManager&&) = delete;
		ClassicDispatcherManager& operator=(const ClassicDispatcherManager&) = delete;
		ClassicDispatcherManager& operator=(ClassicDispatcherManager&&) = delete;

	private:
		void WorkerThread(std::stop_token st)
		{
			while (true)
			{
				m_event.Wait();	// This thread is allowed to process
				TaskData data;
				while (Pop(&data))
				{
					// Processing data
					m_processedCount.fetch_add(1, std::memory_order_relaxed);
				}

				if (st.stop_requested())
				{
					m_event.Set();
					break;
				}
			}
		}

		std::atomic<uint32_t> m_processedCount{ 0 };
		ClassicEvent m_event;
		size_t m_numThreads;
		std::mutex m_mutex;
		std::queue<TaskData> m_queue;
		std::vector<std::jthread> m_threads;
	};
}
