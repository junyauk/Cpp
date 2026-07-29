#pragma once
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <vector>
#include <optional>
#include <atomic>
#include <chrono>
#include <future>

namespace LambdaImprovements
{
	// Note:
	//
	// std::packaged_task<>
	// 
	// It returns a packaged object contains function object and promise.
	//
	//	 int add(int a, int b);
	// 
	//	 // Create a package of function object and promise
	//	 auto task = std::packaged_task<int()>( std::bind(add, 2, 3) );
	// 
	//	 // Getting future that returns int
	//	 std::future<int> result = task->get_future();
	// 
	//	 // Run on thread
	//	 std::thread([task](){ (*task)();}).detach();	
	// 
	//	 // Get the result
	//	 std::cout << "Result = " << result.get() << std::endl;
	//




	class DynamicPriorityTaskDispatcher_AutoShrink
	{
	public:
		using Task = std::function<void()>;
		class TaskItem
		{
		public:
			int priority;
			Task func;
			bool operator<(const TaskItem& other) const
			{
				return priority < other.priority;
			}

		};
		DynamicPriorityTaskDispatcher_AutoShrink(
			size_t minWorkers = 2,
			size_t maxWorkers = std::thread::hardware_concurrency(),
			std::chrono::milliseconds idleTimeout = std::chrono::milliseconds(1500))
			: m_minWorkers(minWorkers)
			, m_maxWorkers(maxWorkers)
			, m_idleTimeout(idleTimeout)
		{
			for (auto i = 0; i < m_minWorkers; ++i)
			{
			}
		}
		~DynamicPriorityTaskDispatcher_AutoShrink()
		{
			{
				std::unique_lock<std::mutex> ul(m_mutex);
				m_stop = true;
			}
			m_cv.notify_all();

			for (auto& w : m_workers)
			{
				if (w.joinable()) w.join();
			}
		}

		template<typename F, typename...Args>
		auto enqueue(const int priority, F&& func, Args&&... args)
		{
			using ReturnType = std::invoke_result_t<F, Args...>;
			auto task = std::make_shared<std::packaged_task<ReturnType()>>(
					std::bind(std::forward<F>(func), std::forward<Args>(args)...));
			{
				std::unique_lock<std::mutex> ul(m_mutex);
				m_tasks.push(TaskItem{ priority, [task]() {(*task)(); } });
				// or 
//				m_tasks.emplace(priority, [task]() {(*task)(); });
			}
			m_cv.notify_one();
			adjustWorkerCount();

			return task->get_future();

		}
	private:
		void workerLoop()
		{
			while (true)
			{
				TaskItem task;
				{
					std::unique_lock<std::mutex> ul(m_mutex);

					if (!m_cv.wait_for(ul, m_idleTimeout, [this] {return m_stop || !m_tasks.empty(); }))
					{
						if (m_tasks.size() > m_minWorkers)
						{
							auto id = std::this_thread::get_id();
							auto it = std::find_if(m_workers.begin(), m_workers.end(),
								[id](std::thread& t) {return t.get_id() == id; });
							if (it != m_workers.end())
							{
								std::thread leaving = std::move(*it);
								m_workers.erase(it);
								ul.unlock();
								if (leaving.joinable())
								{
									leaving.join();
								}
							}
							return;
						}
						continue;
					}
					if (m_stop && m_tasks.empty())
					{
						return;
					}
					auto t = m_tasks.top();
					m_tasks.pop();
					task = std::move(t);
				}
				if (task.priority >= 0)
				{
					task.func();
				}
			}
		}

		void adjustWorkerCount()
		{
			std::unique_lock<std::mutex> ul(m_mutex);
			size_t taskCount = m_tasks.size();
			size_t workerCount = m_workers.size();

			if (taskCount > workerCount && workerCount < m_maxWorkers)
			{
				m_workers.emplace_back(&DynamicPriorityTaskDispatcher_AutoShrink::workerLoop, this);
			}
		}

		// Conditions need to be freed last
		std::mutex m_mutex;
		std::condition_variable m_cv;
		std::atomic<bool> m_stop;

		// Needs to be freed after threads
		std::priority_queue<TaskItem> m_tasks;

		// For threads
		size_t m_minWorkers;
		size_t m_maxWorkers;
		const std::chrono::milliseconds m_idleTimeout;

		// Needs to be freed first
		std::vector<std::thread> m_workers;
	};

}
