#pragma once
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <functional>
#include <future>
#include <condition_variable>

namespace Ex01_ImagePipeline
{
	class ThreadPool
	{
	private:
		std::queue<std::move_only_function<void()>> m_tasks; // Better than std::function. This can handle non-copyable objects.
		std::mutex m_mutex;
		std::condition_variable_any m_cv;
		std::vector<std::jthread> m_workers; // Threads will be released at destractor
		bool m_stopped = false;

		void worker(std::stop_token st)
		{
			while (!st.stop_requested())	// Loop until stop requested
			{
				std::move_only_function<void()> task;
				{
					std::unique_lock lock(m_mutex); // Lock for accessing m_tasks
					m_cv.wait(lock, st, [this]()
						{
							return m_stopped		// Go if stopped for exiting 
								| !m_tasks.empty();	// Go if there is task for procssing
						});

					if (m_tasks.empty())
					{
						if (m_stopped || st.stop_requested())
						{
							break;		// Tasks is empty, and stop requested, terminate this thread
						}
						else
						{
							continue;	// Tasks is empty, but keep running this thread
						}
					}
					// Ready to pop a task from queue
					task = std::move(m_tasks.front());
					m_tasks.pop();
				}
				if (task) task();
			}
		}
	public:
		ThreadPool(size_t numThreads = 0)
		{
			// If numThreads is not specified, ask hardware
			numThreads = (numThreads == 0) ? std::max(1u, std::thread::hardware_concurrency()) : numThreads;

			for (size_t i = 0; i < numThreads; ++i)
			{
				// Note:
				// std::jthread has got stop_source internally,
				// and the specified 1st param of the lamda is 'std::stop_token',
				// jthread will set the token that linked to the internal stop_source.
				// So this 'st' comes from inside of jthread.
				m_workers.emplace_back([this](std::stop_token st) 
					{
						this->worker(st);
					});
			}
		}
		~ThreadPool()
		{
			stop();
		}

		template<typename F, typename... Args>
		auto enqueue(F&& f,Args&&... args )	// Use Perfect Forwarding "&&" that passes 'f' as it is
			-> std::future<std::invoke_result_t<F, Args...>>
			// Note:
			// enqueue(F f):
			//  If 'f' is non-copyable or move only lambda or function object,
			//  it will cause compile error, because 'f' wil be copied.
			// enqueue(const F& f):
			//  It can accept non-copyable object, the f become 'const'
			//  that can't be std::move(f), and it will need to copy somewhere anyway.
			// enqueue(F&& f):
			//  'f' will never be copied, it is forwarded as it is.
		{
			// Deduce the return value of 'f'.
			using ReturnType = std::invoke_result_t<F, Args...>;

			// Create a single object containing function and args
			auto boundTask = std::bind_front(std::forward<F>(f), std::forward<Args>(args)...); // Do not use old std::bind

			// Create packaged_task
			std::packaged_task<ReturnType()> task(std::move(boundTask));
			std::future<ReturnType> futureResult = task.get_future();

			{
				// Lock before pushing a task
				std::scoped_lock lock(m_mutex);
				if (m_stopped)
				{
					throw std::runtime_error("Enqueue failed: ThreadPool is stopped.");
				}

				// Note:
				// You can't push multiple type of objects to std::queue. It is not like std::tuple
				// std::packaged_task<> can have different type of return value
				// So the packaged_task needs to be wrapped in a simple lambda for pushing to the queue.
				// push a lambda calling the packaged_task
				m_tasks.push([task = std::move(task)]() mutable	// mutable is required, it lets the task is changable (removing const).
					{
						// Note:
						// The 'task' is originally std::packaged_task<>.
						// After it was captured, it becomes 'const'.
						// However invoking 'task' will change internal state.
						// So 'mutable' is required for removing 'const'.
						task(); 
					});
			}
			// Let threads know a task is available in the queue
			m_cv.notify_one();

			return futureResult;
		}
		void stop()
		{
			{
				std::scoped_lock lock(m_mutex);
				m_stopped = true;
			}
			m_cv.notify_all();

			for (auto& worker : m_workers)
			{
				if (worker.joinable())
				{
					worker.request_stop();
				}
			}
		}
	};

}
