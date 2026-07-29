#pragma once
#include <thread>
#include <coroutine>
#include <chrono>
#include <vector>
#include <mutex>
#include <algorithm>

class TimerQueue
{
private:
	struct TimerItem
	{
		std::chrono::steady_clock::time_point expiration_time;
		std::coroutine_handle<> handle;

		bool operator>(const TimerItem& other) const
		{
			return expiration_time > other.expiration_time;
		}
	};

	std::vector<TimerItem> m_queue;
	std::mutex	m_mutex;
	std::thread m_thread;
	bool m_stop = false;

	void run()
	{
		while (!m_stop)
		{
			std::unique_lock<std::mutex> ul(m_mutex);

			if (m_queue.empty())
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
				continue;
			}

			auto& item = m_queue.front();
			if (item.expiration_time <= std::chrono::steady_clock::now())
			{
				std::coroutine_handle<> h = item.handle;
				m_queue.erase(m_queue.begin());
				ul.unlock();

				if (h)
				{
					h.resume();
				}
			}
			else
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
		}
	}
public:
	TimerQueue()
	{
		m_thread = std::thread(&TimerQueue::run, this);
	}
	~TimerQueue()
	{
		m_stop = true;
		if (m_thread.joinable())
		{
			m_thread.join();
		}
	}

	void add_timer(std::coroutine_handle<> handle, int milliseconds)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_queue.emplace_back(
			std::chrono::steady_clock::now() + std::chrono::milliseconds(milliseconds),
			handle
		);
	}

};

inline TimerQueue& get_timer_queue()
{
	static TimerQueue instance;
	return instance;
}


