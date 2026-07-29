#pragma once
#include <concepts>
#include <functional>
#include <type_traits>
#include "simple_logger.h"

using namespace SimpleLogger;

namespace Ex02_JobSystem
{
	template<typename F, typename... Args>
	concept JobCallable =
		std::is_invocable_r_v<void, F, Args...>;

	class Job
	{
	private:
		// Note:
		// Since Job class has got move_only_function, this class becomes MOVE ONLY.
		// Implicitly compiler remove copy constructor and operator
		std::move_only_function<void()> m_func;	

	public:
		template<typename F, typename... Args>
		requires JobCallable<F, Args...>	// Check if it's calable
		Job(F&& func, Args&&... args)
		{
			// Using std::bind_front
			m_func = std::bind_front(std::forward<F>(func), std::forward<Args>(args)...);
			// Using lambda
//			m_func = [func = std::forward<F>(func), ...args = std::forward<Args>(args)]() mutable
//				{
//					std::invoke(func, std::move(args)...);
//				};
		}

		void operator()()
		{
			LOG(INFO) << "Job::operator()() ->";
			m_func();
			LOG(INFO) << "Job::operator()() <-";
		}
	};
}
