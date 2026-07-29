#pragma once
#include <coroutine>
#include <iostream>
#include <thread>
#include <chrono>
#include <utility>
#include <random>

namespace CoroutineSamples
{
	class AsyncTask
	{
	public:
		struct promise_type
		{
			AsyncTask get_return_object()
			{
				return AsyncTask{ std::coroutine_handle<promise_type>::from_promise(*this) };
			}
			std::suspend_always initial_suspend() noexcept { return {}; }
			std::suspend_always final_suspend() noexcept { return {}; }
			void return_void() noexcept {}
			void unhandled_exception() { std::terminate(); }
		};

		using handle_type = std::coroutine_handle<promise_type>;

		explicit AsyncTask(handle_type h) : handle(h) {}
		~AsyncTask()
		{
			if (handle) handle.destroy();
		}

		// Copy constructors need to be disabled
		AsyncTask(const AsyncTask&) = delete;
		AsyncTask& operator=(const AsyncTask&) = delete;

		// Move constructor should disable the provided old one
		AsyncTask(AsyncTask&& rhs) noexcept : handle(rhs.handle)
		{
			rhs.handle = nullptr;
		}
		AsyncTask& operator=(const AsyncTask&& rhs) = delete;

		void start()
		{
			if (handle && !handle.done())
			{
				handle.resume();
			}
		}

		bool done() const noexcept { return !handle || handle.done(); }

	private:
		handle_type handle{};
	};

	struct SleepAwaiter
	{
		int milliseconds;
		bool await_ready() const noexcept { return false; }
		void await_suspend(std::coroutine_handle<> h)
		{
			std::thread([h, ms = milliseconds]()
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(ms));
					h.resume();

				}).detach();
		}
		void await_resume() const noexcept {}
	};

	AsyncTask asyncFunction()
	{
		std::cout << "Task started.\n";
		co_await SleepAwaiter(1000);
		std::cout << "Task resumed after 1 second.\n";
		co_await SleepAwaiter(500);
		std::cout << "Task resumed after 1.5 seconds in total.\n";
	}

	// ---------------------------------------------------------------------------
	struct RandomAwaiter
	{
		bool await_ready() const noexcept
		{
			std::cout << "RandomAwaiter::await_ready() was called.\n";
			return false;
		}

		void await_suspend(std::coroutine_handle<> h)
		{
			std::cout << "RandomAwaiter::await_suspend() was called.\n";
			static std::mt19937 gen(std::random_device{}());

			std::uniform_int_distribution<> dist(1, 100);
			int value = dist(gen);

			std::cout << "[RandomAwaiter] generated value = " << value << std::endl;

			result = value;
			h.resume();
		}
		
		int await_resume() const
		{
			return result;
		}
	private:
		int result{};
	};

	struct Task
	{
		struct promise_type
		{
			Task get_return_object()
			{
				return Task{ std::coroutine_handle<promise_type>::from_promise(*this) };
			}
			std::suspend_always initial_suspend() noexcept { return{}; }
			std::suspend_always final_suspend() noexcept { return{}; }
			void return_void() { }
			void unhandled_exception() { std::terminate(); }
		};

		std::coroutine_handle<promise_type> handle;

		explicit Task(std::coroutine_handle<promise_type> h) : handle(h) {}
		~Task()
		{
			if (handle) handle.destroy();
		}

		void resume()
		{
			if (handle && !handle.done()) handle.resume();
		}
		bool done() const { return handle.done(); }
	};


	Task randomCoroutine()
	{
		std::cout << "randomCoroutine() started.\n";
		int value = co_await RandomAwaiter();
		std::cout << "Coroutine resumed with random value : " << value << std::endl;
	}
}
