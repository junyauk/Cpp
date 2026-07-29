#pragma once
#include <vector>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <future>
#include <variant>
#include <utility>
#include <type_traits>
#include <exception>

#include "CancelToken.h"

namespace LambdaImprovements
{
	template<typename R>
	class GatherDispatcher
	{
		static_assert(!std::is_void<R>::value, "GatherDispatcher<R> requires non-void R. Provide specialization for void if needed.");
	public:
		using ResultVariant = std::variant<R, std::exception_ptr>;

		GatherDispatcher() = default;
		
		template<typename F, typename... Args>
		void submit(F&& func, Args&&... args)
		{
			auto bound = std::bind(std::forward<F>(func), std::forward<Args>(args)...);
			std::function<R()> callable = std::move(bound);
			std::lock_guard<std::mutex> lock(m_mutex);
			m_tasks.emplace_back(std::move(callable));
		}

		std::vector<std::future<R>> runAll()
		{
			std::vector<std::function<R()>> tasksCopy;
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				tasksCopy = m_tasks;
			}
			std::vector<std::future<R>> futures;
			futures.reserve(tasksCopy.size());
			for (auto& t : tasksCopy)
			{
				futures.emplace_back(std::async(std::launch::async, t));
			}
			return futures;
		}

		static std::vector<ResultVariant> gather(std::vector<std::future<R>>& futures)
		{
			std::vector<ResultVariant> results;
			results.reserve(futures.size());
			for (auto& fut : futures)
			{
				try
				{
					R ret = fut.get();
					results.emplace_back(std::move(ret));
				}
				catch (...)
				{
					results.emplace_back(std::current_exception());
				}
			}
			return results;
		}

		void clear()
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			m_tasks.clear();
		}

		static std::vector<std::exception_ptr> extractExceptions(const std::vector<ResultVariant>& results)
		{
			std::vector<std::exception_ptr> exceptions;
			for (const auto& r : results)
			{
				if (std::holds_alternative<std::exception_ptr>(r))
				{
					exceptions.push_back(std::get<std::exception_ptr>(r));
				}
			}
			return exceptions;
		}

		std::size_t size() const
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			return m_tasks.size();
		}

	private:
		std::mutex m_mutex;
		std::vector<std::function<R()>> m_tasks;
	};
}
