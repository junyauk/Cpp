#pragma once
#include <queue>
#include <vector>
#include <thread>
#include <functional>
#include <mutex>
#include <future>
#include <condition_variable>
#include <iostream>
#include "CancelToken.h"

namespace LambdaImprovements
{
	class CancellableTaskDispatcher
	{
	public:
		CancellableTaskDispatcher(size_t threadCount = std::thread::hardware_concurrency())
			: m_stop(false)
		{
			for (size_t i = 0; i < threadCount; ++i)
			{
				m_workers.emplace_back(&CancellableTaskDispatcher::workerLoop, this);
			}
		}
		~CancellableTaskDispatcher()
		{
			{
				std::unique_lock<std::mutex> lock(m_mutex);
				m_stop = true;
			}
			m_cv.notify_all();
			for (std::thread& worker : m_workers)
			{
				if (worker.joinable())
				{
					worker.join();
				}
			}
		}

		template<typename Func, typename Token, typename... Args>
		auto enqueue(Func&& func, Token&& token, Args&&... args) -> std::future<std::invoke_result_t<Func, Args...>>
		{
			using ReturnType = std::invoke_result_t<Func, Args...>;
			auto taskPtr = std::make_shared<std::packaged_task<ReturnType()>>(
				[func = std::forward<Func>(func),
				 token = std::forward<Token>(token),
				 argsTuple = std::make_tuple(std::forward<Args>(args)...)
				]() mutable -> ReturnType
				{
					if (token.isCancelled())
					{
						throw std::runtime_error("Task cancelled before start");
					}
					return std::apply(
						[&](auto&&... unpackedArgs) -> ReturnType
						{
							if (token.isCancelled())
							{
								throw std::runtime_error("Task cancelled before execution");
							}
							return func(std::forward<decltype(unpackedArgs)>(unpackedArgs)...);
						},
						std::move(argsTuple)
					);
				}
			);
			std::future<ReturnType> resultFuture = taskPtr->get_future();

			{
				std::unique_lock<std::mutex> lock(m_mutex);
				if (m_stop)
				{
					throw std::runtime_error("Dispatcher stopped");
				}
				m_tasks.emplace([taskPtr]() { (*taskPtr)(); });
			}

			m_cv.notify_one();
			return resultFuture;
		}

	private:
		void workerLoop()
		{
			while (true)
			{
				Task task;
				{
					std::unique_lock<std::mutex> lock(m_mutex);
					m_cv.wait(lock, [this]() { return m_stop || !m_tasks.empty(); });
					if (m_stop && m_tasks.empty())
					{
						lock.unlock();
						break;
					}
					task = std::move(m_tasks.front());
					m_tasks.pop();
				}

				try
				{
					task();
				}
				catch(const std::exception& e)
				{
					std::cerr << "[Dispatcher error] " << e.what() << std::endl;
				}
			}
		}
		using Task = std::function<void()>;
		std::mutex m_mutex;
		std::condition_variable m_cv;
		bool m_stop;

		std::queue<Task> m_tasks;
		std::vector<std::thread> m_workers;
	};
}
