#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>
#include <thread>
#include <iostream>
#include <atomic>
#include <memory>

namespace LambdaImprovements
{
	class LogDispatcher
	{
	private:
		std::queue<std::string> m_logQueue;
		std::mutex m_mutex;
		std::condition_variable m_cv;
		std::atomic<bool> m_stopRequested{ false };
		std::thread m_worker;
	public:
		LogDispatcher()
		{
			m_worker = std::thread([this]()
				{
					while (true)
					{
						std::unique_lock<std::mutex> ul(m_mutex);
						m_cv.wait(ul, [this]()
							{
								return !m_logQueue.empty() || m_stopRequested;
							});
						if (m_stopRequested && m_logQueue.empty())
						{
							break;
						}
						auto msg = std::move(m_logQueue.front());
						m_logQueue.pop();
						ul.unlock();

						std::cout << "[LOG] " << msg << std::endl;
					}
				});
		}

		~LogDispatcher()
		{
			if (m_worker.joinable())
			{
				stop();
			}
		}

		void enqueueLog(std::string msg)
		{
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				m_logQueue.push(std::move(msg));
			}
			m_cv.notify_one();
		}

		void stop()
		{
			if (!m_stopRequested.exchange(true))
			{
				m_cv.notify_all();
				if (m_worker.joinable())
				{
					m_worker.join();
				}
			}
		}

	};

}
