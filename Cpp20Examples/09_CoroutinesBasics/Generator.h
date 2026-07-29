#pragma once
#include <coroutine>
#include <optional>
#include <iostream>

namespace CoroutineSamples
{
	// ------------------------------------------------------------------------
	template<typename T>
	class Generator
	{
	public:
		struct promise_type;
		using handle_type = std::coroutine_handle<promise_type>;
		struct promise_type
		{
			std::optional<T> current_value;
			Generator get_return_object() {
				return Generator{ handle_type::from_promise(*this) };
			}
			std::suspend_always initial_suspend() { return {}; }
			std::suspend_always final_suspend() noexcept { return {}; }
			std::suspend_always yield_value(T value) {
				current_value = value;
				return {};
			}
			void return_void() {}
			void unhandled_exception() {std::terminate();}
		};
		Generator(handle_type h) : coro(h) {}
		~Generator() { if (coro) coro.destroy(); }

		Generator(const Generator&) = delete;
		Generator& operator=(const Generator&) = delete;
		Generator(Generator&& other) noexcept : coro(other.coro) { other.coro = nullptr; }

		Generator& operator=(Generator&& other) noexcept {
			if (this != &other) {
				if (coro) coro.destroy();
				coro = other.coro;
				other.coro = nullptr;
			}
			return *this;
		}
		bool next()
		{
			if (!coro || coro.done())
			{
				return false;
			}
			coro.resume();
			return !coro.done();
		}

		T current() const
		{
			return *coro.promise().current_value;
		}

	private:
		handle_type coro;
	};

	Generator<int> count_up_to(int n)
	{
		for (int i = 1; i <= n; ++i)
		{
			co_yield i;
		}
	}
}
