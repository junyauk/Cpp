#include "pch.h"
#include "DynamicPriorityTaskDispatcher.h"


namespace LambdaImprovements
{
	DynamicPriorityTaskDispatcher::DynamicPriorityTaskDispatcher(size_t minThreads, size_t maxThreads)
		: m_minThreads(minThreads), m_maxThreads(maxThreads)
	{
		EZLog("DynamicPriorityTaskDispatcher ->\n");
	}

	DynamicPriorityTaskDispatcher::~DynamicPriorityTaskDispatcher()
	{
		EZLog("~DynamicPriorityTaskDispatcher ->\n");
		stop();
		EZLog("~DynamicPriorityTaskDispatcher <-\n");
	}

	void DynamicPriorityTaskDispatcher::start()
	{
		EZLog("start ->\n");
		std::unique_lock<std::mutex> ul(m_mutex);
		m_stopping = false;

		for (auto i = 0; i < m_minThreads; ++i)
		{
			m_workers.emplace_back(&DynamicPriorityTaskDispatcher::workerLoop, this);
		}

		m_manager = std::thread(&DynamicPriorityTaskDispatcher::managerLoop, this);
		EZLog("start <-\n");
	}
	void DynamicPriorityTaskDispatcher::stop()
	{
		EZLog("stop ->\n");
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			m_stopping = true;
		}
		m_cv.notify_all();

		for (auto& w : m_workers)
		{
			if (w.joinable())
			{
				w.join();
			}
		}
		m_workers.clear();

		if (m_manager.joinable())
		{
			m_manager.join();
		}
		EZLog("stop <-\n");
	}

	void DynamicPriorityTaskDispatcher::enqueue(Task task, int priority)
	{
		EZLog("enqueue ->\n");
		{
			std::unique_lock<std::mutex> ul(m_mutex);
			EZLog("before emplace\n");
			m_tasks.emplace(priority, std::move(task));
			EZLog("after emplace\n");
		}
		m_cv.notify_one();
		EZLog("enqueue <-\n");
	}

	size_t DynamicPriorityTaskDispatcher::getWorkerCount()
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		return m_workers.size();

	}
	size_t DynamicPriorityTaskDispatcher::getQueueSize()
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		return m_tasks.size();
	}

	void DynamicPriorityTaskDispatcher::workerLoop()
	{
		EZLog("workerLoop ->\n");
		while (true)
		{
			Task task;
			{
				std::unique_lock<std::mutex> ul(m_mutex);
				m_cv.wait(ul, [this]() {return m_stopping || !m_tasks.empty(); });

				if (m_stopping && m_tasks.empty())
				{
					break;
				}

				auto t = m_tasks.top();
				m_tasks.pop();
				task = t.func;
			}
			task();
		}
		EZLog("workerLoop <-\n");
	}
	void DynamicPriorityTaskDispatcher::managerLoop()
	{
		EZLog("managerLoop ->\n");
		while (!m_stopping)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(50));

			size_t queueSize;
			size_t workerCount;

			{
				std::unique_lock<std::mutex> lock(m_mutex);
				queueSize = m_tasks.size();
				workerCount = m_workers.size();
			}

			if (queueSize > workerCount * 2 && workerCount < m_maxThreads)
			{
				std::cout << "[Manager] increasing threads: " << workerCount + 1 << std::endl;
				adjustWorkerCount(workerCount + 1);
			}
			else if (queueSize < workerCount / 2 && workerCount > m_minThreads)
			{
				std::cout << "[Manager] decreasing threads: " << workerCount - 1 << std::endl;
				adjustWorkerCount(workerCount - 1);
			}
		}
		EZLog("managerLoop <-\n");
	}
	void DynamicPriorityTaskDispatcher::adjustWorkerCount(size_t desired)
	{
		EZLog("adjustWorkerCount ->\n");
		std::unique_lock<std::mutex> ul(m_mutex);

		if (desired > m_workers.size())
		{
			size_t addCount = desired - m_workers.size();
			EZLog(" adding workerLoop\n");
			for (auto i = 0; i < addCount; ++i)
			{
				m_workers.emplace_back(&DynamicPriorityTaskDispatcher::workerLoop, this);
			}
			EZLog(" adding workerLoop done\n");
		}
		else if (desired < m_workers.size())
		{
			size_t removeCount = m_workers.size() - desired;
			EZLog(" removing workerLoop\n");

			ul.unlock();
			for (auto i = 0; i < removeCount; ++i)
			{
				enqueue([]
					{
						std::this_thread::yield();
					}, -1);
			}
			EZLog(" removing workerLoop done\n");
		}
		EZLog("adjustWorkerCount <-\n");
	}
}

