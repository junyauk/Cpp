#pragma once
#include <queue>
#include <deque>
#include <mutex>
#include <optional>
#include "job.h"

namespace Ex02_JobSystem
{
	template<typename T>
	class WorkStealingQueue
	{
	private:
		std::deque<T> m_deque;
		mutable std::mutex m_mutex;
	public:
		void push(T job)
		{
			std::scoped_lock<std::mutex> lock(m_mutex);
			m_deque.push_back(std::move(job));
		}
		std::optional<T> pop()
		{
			std::scoped_lock<std::mutex> lock(m_mutex);

			if (m_deque.empty())
			{
				return std::nullopt;
			}
			T job = std::move(m_deque.back());
			m_deque.pop_back();
			return job;
		}
		std::optional<T> steal()
		{
			std::scoped_lock<std::mutex> lock(m_mutex);
			if (m_deque.empty())
			{ 
				return std::nullopt;
			}
			T job = std::move(m_deque.front());
			m_deque.pop_front();
			return job;
		}
		bool empty() const
		{
			std::scoped_lock<std::mutex> lock(m_mutex);
			return m_deque.empty();
		}
	};
}
