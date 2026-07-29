#pragma once
#include <coroutine>
#include <optional>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

namespace ChainTaskSamples
{
	template<typename T>
	struct ChainTask
	{
		struct promise_type
		{
			std::optional<T> m_t;
			std::exception_ptr m_exptr;
			ChainTask get_return_object()
			{
				return ChainTask{ std::coroutine_handle<promise_type>::from_promise(*this) };
			}
			std::suspend_always initial_suspend() const noexcept { return{}; }
			std::suspend_always final_suspend() const noexcept { return{}; }
			void return_value(T t) { m_t = std::move(t); }
			void unhandled_exception() { m_exptr = std::current_exception(); }
		};

		using handle_type = std::coroutine_handle<promise_type>;
		handle_type m_h;
		explicit ChainTask(handle_type h) : m_h(h) {}
		ChainTask(const ChainTask&) = delete;
		ChainTask& operator=(const ChainTask&) = delete;
		ChainTask(ChainTask&& o) noexcept : m_h(o.m_h) { o.m_h = {}; }
		~ChainTask()
		{
			if (m_h) m_h.destroy();
		}

		auto operator co_await()
		{
			struct Awaiter
			{
				handle_type m_h;
				bool await_ready() const noexcept { return false; }
				void await_suspend(std::coroutine_handle<> h)
				{
					m_h.resume();
					h.resume();
				}
				T await_resume()
				{
					if (m_h.promise().m_exptr) std::rethrow_exception(m_h.promise().m_exptr);
					if (m_h.promise().m_t.has_value())
					{
						return std::move(m_h.promise().m_t.value());
					}
					throw std::runtime_error("No value");
				}
			};
			return Awaiter{ m_h };
		}

		T get()
		{
			if (!m_h.done()) m_h.resume();
			if (m_h.promise().m_exptr) std::rethrow_exception(m_h.promise().m_exptr);
			return *m_h.promise().m_t;
		}
	};

	ChainTask<int> step1()
	{
		std::cout << "[TID:" << std::this_thread::get_id << "] Step 1:" << std::endl;
		co_return 10;
	}
	ChainTask<int> step2(int input)
	{
		std::cout << "[TID:" << std::this_thread::get_id << "] Step 2:" << std::endl;
		co_return input * 2;
	}
	ChainTask<std::string> chainSample()
	{
		std::cout << "[TID:" << std::this_thread::get_id << "] Step 3:" << std::endl;
		int v1 = co_await step1();
		int v2 = co_await step2(v1);

		std::string result = "Result is " + std::to_string(v2);

		co_return result;
	}

}