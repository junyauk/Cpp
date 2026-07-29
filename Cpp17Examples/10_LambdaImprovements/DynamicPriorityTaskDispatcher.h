#pragma once
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <vector>
#include <atomic>
#include <iostream>
#include <sstream>

namespace LambdaImprovements
{
	inline void EZLog(std::string str)
	{
		std::stringstream ss;
		ss << "[TID:" << std::this_thread::get_id() << "] " << str;
		std::cout << ss.str();
	}

	class DynamicPriorityTaskDispatcher
	{
	public:
		using Task = std::function<void()>;

		explicit DynamicPriorityTaskDispatcher(size_t minThreads = 2, size_t maxThreads = 8);
		~DynamicPriorityTaskDispatcher();

		void enqueue(Task task, int priority);
		void start();
		void stop();

		size_t getWorkerCount();
		size_t getQueueSize();
	private:
		struct TaskItem
		{
			int priority;
			Task func;
			TaskItem(const int p, Task f) : priority(p), func(f) {}

			bool operator<(const TaskItem& other) const
			{
				return priority < other.priority;
			}
		};

		void workerLoop();
		void managerLoop();
		void adjustWorkerCount(size_t desired);

		std::atomic<bool> m_stopping{ false };
		std::mutex m_mutex;
		std::condition_variable m_cv;
		std::priority_queue<TaskItem> m_tasks;
		std::vector<std::thread> m_workers;
		std::thread m_manager;

		size_t m_minThreads;
		size_t m_maxThreads;
	};

}
