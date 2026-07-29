#pragma once
#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>

namespace LambdaImprovements
{
	class TaskDispatcher
	{
	private:
		std::queue<std::function<void()>> m_tasks;
		bool m_stop{ false };
		std::mutex m_mutex;
		std::condition_variable m_cv;
		std::thread m_worker;

		void run()
		{
			while (true)
			{
				std::function<void()> task;
				{
					std::unique_lock<std::mutex> ul(m_mutex);
					m_cv.wait(ul, [this]() {return m_stop || !m_tasks.empty(); });

					if (m_stop && m_tasks.empty())
					{
						break;
					}

					task = std::move(m_tasks.front());
					m_tasks.pop();
				}
				task();
			}
		}
		
	public:
		TaskDispatcher()
		{
			m_worker = std::thread([this](){ run(); });
		}
		~TaskDispatcher()
		{
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				m_stop = true;
			}
			m_cv.notify_all();
			if (m_worker.joinable())
			{
				m_worker.join();
			}
		}

		template<typename F, typename... Args>
		auto dispatch(F&& func, Args&&... args)
		{
			using ReturnT = std::invoke_result_t<F, Args...>;
			auto promise = std::make_shared<std::promise<ReturnT>>();
			auto future = promise->get_future();
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				m_tasks.emplace([promise,
					func = std::forward<F>(func),
					tup = std::make_tuple(std::forward<Args>(args)...)]() mutable
				{
					try
					{
						if constexpr (std::is_void_v<ReturnT>)
						{
							std::apply(func, std::move(tup));
							promise->set_value();
						}
						else
						{
							promise->set_value(std::apply(func, std::move(tup)));
						}
					}
					catch (...)
					{
						promise->set_exception(std::current_exception());
					}
				});
			}

		m_cv.notify_all();
		return future;
		}
	};

}

