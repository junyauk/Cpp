#pragma once
#include <coroutine>
#include <string>
#include <iostream>
#include <optional>


namespace TaskTemplateExamples
{
	template<typename T>
	struct Task
	{
		struct promise_type
		{
			T m_t;
			std::exception_ptr m_exptr;
			Task get_return_object()
			{
				return Task{ std::coroutine_handle<promise_type>::from_promise(*this) };
			}
			std::suspend_always initial_suspend() const noexcept { return{}; }
			std::suspend_always final_suspend() const noexcept { return{}; }

			void return_value(T t) { m_t = t; }
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
			if (m_h) m_h.destroy();
		}

		T get()
		{
			if (m_h)
			{
				m_h.resume();
				if (m_h.promise().m_exptr) std::rethrow_exception(m_h.promise().m_exptr);
				return std::move(m_h.promise().m_t);
			}
			throw std::runtime_error("No coroutine");
		}
	};

	Task<int> compute_value()
	{
		co_return 42;
	}

	Task<std::string> make_message()
	{
		co_return std::string("Hello, World!");
	}

	void run()
	{
		auto task1 = compute_value();
		int value = task1.get();
		std::cout << "Computed value: " << value << std::endl;
		auto task2 = make_message();
		std::string message = task2.get();
		std::cout << "Message: " << message << std::endl;
	}

	template<typename T>
	struct TaskCoAwait
	{
		struct promise_type
		{
			std::optional<T> m_t;
			TaskCoAwait get_return_object()
			{
				return TaskCoAwait{ std::coroutine_handle<promise_type>::from_promise(*this) };
			}

			std::suspend_always initial_suspend() const noexcept { return{}; }
			std::suspend_always final_suspend() const noexcept { return {}; }

			void return_value(T v) { m_t = v; }
			void unhandled_exception() { std::terminate(); }
		};

		using handle_type = std::coroutine_handle<promise_type>;
		handle_type m_h;

		explicit TaskCoAwait(handle_type h) : m_h(h) {}
		TaskCoAwait(const TaskCoAwait&) = delete;
		TaskCoAwait& operator=(const TaskCoAwait&) = delete;
		TaskCoAwait(TaskCoAwait&& o) noexcept : m_h(o.m_h) { o.m_h = {}; }
		~TaskCoAwait()
		{
			if (m_h) m_h.destroy();
		}

		bool await_ready() const noexcept
		{
			// true: ready for await_resume, false: need await_suspend
			return m_h.promise().m_t.has_value();
		}
		void await_suspend(std::coroutine_handle<> h)
		{
			m_h.resume();
			h.resume();
		}

		T await_resume()
		{
			if (m_h && m_h.promise().m_t.has_value())
			{
				return std::move(m_h.promise().m_t.value());
			}
			return T{};
		}
	};

	TaskCoAwait<int> comppute_value_co_await(int a, int b)
	{
		std::cout << "Compute values co_await: " << a << " and " << b << std::endl;
		co_return a + b; // TaskCoAwait<int>::promise_type::return_value will be called.
	}

	struct TaskVoid
	{
		struct promise_type
		{
			TaskVoid get_return_object()
			{
				return TaskVoid{ std::coroutine_handle<promise_type>::from_promise(*this) };
			}
			std::suspend_always initial_suspend() const noexcept { return{}; }
			std::suspend_always final_suspend() const noexcept { return{}; }
			void return_void() noexcept {}
			void unhandled_exception() { std::terminate(); }
		};

		using handle_type = std::coroutine_handle<promise_type>;
		handle_type m_h;
		explicit TaskVoid(handle_type h) : m_h(h) {}
		TaskVoid(const TaskVoid&) = delete;
		TaskVoid& operator=(const TaskVoid&) = delete;
		TaskVoid(TaskVoid&& o) noexcept : m_h(o.m_h) { o.m_h = {}; }
		~TaskVoid()
		{
			if (m_h) m_h.destroy();
		}
	};

	TaskVoid sample()
	{
		std::cout << "[Sample] before co_await.\n";
		int result = co_await comppute_value_co_await(10, 20);
		std::cout << "[Sample] after co_await. result = " << result << "\n";
		co_return;
	}

	void run_co_await()
	{
		TaskVoid t = sample();
		t.m_h.resume();
	}
}