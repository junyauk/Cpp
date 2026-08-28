#pragma once
#include <Windows.h>
#include "modernevent.h"
#include "../Ex01_SRWLock_CondVar/srwlockwrapper.h"
using namespace Ex01_SRWLock_CondVar;

namespace Ex04_AddressWait_OnceInit
{
	class ModernDispatcherManager
	{
	public:
		ModernDispatcherManager()
		{
			m_numThreads = std::thread::hardware_concurrency();
			for (size_t i = 0; i < m_numThreads; ++i)
			{
				m_threads.emplace_back([&](std::stop_token st) {WorkerThread(st); });
			}
		}

		~ModernDispatcherManager()
		{
			if (!m_threads.empty())
			{
				Stop();
			}
		}

		static ModernDispatcherManager* GetInstance()
		{
			static ModernDispatcherManager instance;
			return &instance; // All threads will share this
		}

		void Push(TaskData data)
		{
			SrwLockExclusive lock(m_lock);
			m_queue.push(data);
			m_event.Set(); // Activate one of threads
		}
		bool Pop(TaskData* data)
		{
			SrwLockExclusive lock(m_lock);
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
		ModernDispatcherManager(const ModernDispatcherManager&) = delete;
		ModernDispatcherManager(ModernDispatcherManager&&) = delete;
		ModernDispatcherManager& operator=(const ModernDispatcherManager&) = delete;
		ModernDispatcherManager& operator=(ModernDispatcherManager&&) = delete;

	private:
		void WorkerThread(std::stop_token st)
		{
			while (true)
			{
				m_event.Wait();	// This thread is allowed to process
				TaskData data;
				while(Pop(&data))
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
		ModernEvent m_event;
		size_t m_numThreads;
		SRWLOCK m_lock = SRWLOCK_INIT;
		std::queue<TaskData> m_queue;
		std::vector<std::jthread> m_threads;
	};
}
