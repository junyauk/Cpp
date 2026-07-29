#pragma once
#include <coroutine>
#include <optional>
#include <iostream>
#include <string>
#include <vector>

namespace TaskWhenAllSample
{
	template<typename T>
	struct Task
	{
		struct promise_type
		{
			std::optional<T> m_v{};
			std::exception_ptr m_exptr{};

			Task get_return_object()
			{
				return Task{ std::coroutine_handle<promise_type>::from_promise(*this) };
			}
			std::suspend_never initial_suspend() const noexcept { return{}; }
			std::suspend_always final_suspend() const noexcept { return{}; }

			void return_value(T v) { m_v = v; }
			void unhandled_exception() { m_exptr = std::current_exception(); }
		};

		using handle_type = std::coroutine_handle<promise_type>;
		handle_type m_h;

		explicit Task(handle_type h) : m_h(h) {}
		Task(const Task&) = delete;
		Task& operator=(const Task&) = delete;
		Task(Task&& o) noexcept : m_h(o.m_h) { o.m_h = {}; }
		~Task()
		{
			if (m_h && !m_h.done()) m_h.resume();
			if (m_h) m_h.destroy();
		}

		T result()
		{
			if (m_h.promise().m_exptr) std::rethrow_exception(m_h.promise().m_exptr);
			return std::move(m_h.promise().m_v);
		}


		T get_sync()
		{
			if (m_h && !m_h.done()) m_h.resume();
			if (m_h.promise().m_exptr) std::rethrow_exception(m_h.promise().m_exptr);
			return *m_h.promise().m_v;
		}

		auto operator co_await() & noexcept
		{
			return Awaiter{ m_h };
		}
		auto operator co_await() const& noexcept
		{
			return Awaiter{ m_h };
		}
		auto operator co_await() && noexcept
		{
			return Awaiter{ m_h };
		}

	private:
		struct Awaiter
		{
			handle_type m_h;
			bool await_ready() const noexcept
			{
				return !m_h || m_h.promise().m_v.has_value() || m_h.done();
			}
			void await_suspend(std::coroutine_handle<> awaiting)
			{
				if (m_h && !m_h.done()) m_h.resume();
				awaiting.resume();
			}
			T await_resume()
			{
				if (m_h.promise().m_exptr) std::rethrow_exception(m_h.promise().m_exptr);
				return *m_h.promise().m_v;
			}
		};

	};

	template<typename T>
	struct WhenAllTask
	{
		struct promise_type
		{
			std::vector<T> m_results;
			std::exception_ptr m_exptr;
			WhenAllTask get_return_object()
			{
				return WhenAllTask{ std::coroutine_handle<promise_type>::from_promise(*this) };
			}
			std::suspend_never initial_suspend() const noexcept { return{}; }
			std::suspend_always final_suspend() const noexcept { return{}; }
			void return_value(std::vector<T> results) { m_results = std::move(results); }
			void unhandled_exception() { m_exptr = std::current_exception(); }
		};
		using handle_type = std::coroutine_handle<promise_type>;
		handle_type m_h;

		explicit WhenAllTask(handle_type h) : m_h(h) {}
		WhenAllTask(const WhenAllTask&) = delete;
		WhenAllTask& operator=(const WhenAllTask&) = delete;
		WhenAllTask(WhenAllTask&& o) noexcept : m_h(o.m_h) { o.m_h = {}; }
		~WhenAllTask()
		{
			if (m_h) m_h.destroy();
		}
		std::vector<T> result()
		{
			if (m_h.promise().m_exptr) std::rethrow_exception(m_h.promise().m_exptr);
			return std::move(m_h.promise().m_results);
		}

		bool await_ready() const noexcept { return false; }
		void await_suspend(std::coroutine_handle<> h)
		{
			if (m_h && !m_h.done()) m_h.resume();
			h.resume();
		}
		std::vector<T> await_resume()
		{
			return result();
		}
	};

	template<typename T>
	WhenAllTask<T> when_all(std::vector<Task<T>> tasks)
	{
		std::vector<T> results;
		results.reserve(tasks.size());
		for (auto& t : tasks)
		{
//			co_await std::suspend_always{};
			T v = co_await t;
			results.push_back(std::move(v));
		}
		co_return results;
	}

	Task<int> computeSquare(int v)
	{
		co_return v * v;
	}

	WhenAllTask<int> parallelSquares()
	{
		std::vector<Task<int>> tasks;
		tasks.push_back(computeSquare(2));
		tasks.push_back(computeSquare(3));
		tasks.push_back(computeSquare(4));

		auto results = co_await when_all(std::move(tasks));
		co_return results;
	}
}


