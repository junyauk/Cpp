#include <coroutine>
#include <iostream>
#include <thread>
#include <chrono>

namespace ValueReturningTaskSamples
{
	template <typename T>
	struct SimpleValueTask
	{
		struct promise_type
		{
			T value;

			SimpleValueTask get_return_object()
			{
				return SimpleValueTask{std::coroutine_handle<promise_type>::from_promise(*this)};
			}

			std::suspend_always initial_suspend() noexcept { return {}; }
			std::suspend_always final_suspend() noexcept { return {}; }

			void return_value(T v) { value = v; }
			void unhandled_exception() { std::terminate(); }
		};

		using handle_type = std::coroutine_handle<promise_type>;
		handle_type coro;

		explicit SimpleValueTask(handle_type h) : coro(h) {}
		~SimpleValueTask() { if (coro) coro.destroy(); }

		bool await_ready() const noexcept { return false; }
		void await_suspend(std::coroutine_handle<> h) noexcept
		{
			coro.resume();
			h.resume();
		}

		T await_resume()
		{
			return coro.promise().value;
		}
	};

	SimpleValueTask<int> compute_immediate(int x)
	{
		co_return x * 2;
	}

	SimpleValueTask<int> compute_delayed(int x)
	{
		std::cout << "delayed computing...\n";
		co_return x + 10;
	}

	SimpleValueTask<int> add_two(int x, int y)
	{
		int a = co_await compute_immediate(x);
		int b = co_await compute_delayed(y);
		co_return a + b;
	}


	SimpleValueTask<int> runner()
	{
		int result = co_await add_two(3, 5);
		std::cout << "result = " << result << std::endl;
		co_return result;
	}

}
