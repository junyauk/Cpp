#pragma once
#include <coroutine>
#include <type_traits>

/**
 * @brief Simple Generator class for C++20 coroutines using co_yield.
 * @tparam T The type of the value yielded by the coroutine.
 * @note This structure is necessary to define the coroutine interface.
 */
template <typename T>
struct Generator
{
	// --- Coroutine Promise Type ---
	struct promise_type
	{
		T current_value; // Stores the value yielded by co_yield

		// 0. Get Coroutine Handle: Called during the initial setup to link the promise to the Generator.
		Generator get_return_object() noexcept
		{
			return Generator{ std::coroutine_handle<promise_type>::from_promise(*this) };
		}

		// 1. Initial Suspension: Coroutine starts suspended, waiting for the first 'next' call.
		std::suspend_always initial_suspend() noexcept { return {}; }

		// 2. Final Suspension: Coroutine suspends at the end, allowing the consumer to check state.
		std::suspend_always final_suspend() noexcept { return {}; }

		// 3. Termination Handling: Handle 'co_return' (often unused for generators)
		void return_void() noexcept {}

		// 4. Exception Handling: Propagate unhandled exceptions.
		void unhandled_exception() { throw; }


		// --------------------------------------------------------------------------
		// For using co_yield
		// 
		// 5. Yield Handling: Suspends and stores the yielded value.
		std::suspend_always yield_value(T value) noexcept
		{
			current_value = std::move(value);
			return {};
		}
	};

	// --- Coroutine Handle and Constructor ---
	using Handle = std::coroutine_handle<promise_type>;
	Handle handle_;

	// Private constructor used by promise_type::get_return_object()
	Generator(Handle h) : handle_(h) {}
	Generator(Generator const&) = delete;
	Generator(Generator&& other) noexcept : handle_(std::exchange(other.handle_, nullptr)) {}
	~Generator() { if (handle_) handle_.destroy(); }

	// --- Iterator for Range-based for loop ---
	struct iterator
	{
		using iterator_category = std::input_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = const T*;
		using reference = const T&;

		Handle handle_ = nullptr; // Current coroutine state

		// Default constructor for end()
		iterator() = default;

		// Iterator constructor: attempts to advance the coroutine for the first element
		iterator(Handle h) : handle_(h) 
		{
			if (handle_ && !handle_.done())
			{
				handle_.resume();	// Resume to execute until the first co_yield
			}
		}

		iterator(const iterator&) = default;
		iterator& operator=(const iterator&) = default;

		iterator(iterator&&) = default;
		iterator& operator=(iterator&&) = default;

		// Dereference: Access the yielded value
		const T& operator*() const
		{
			return handle_.promise().current_value;
		}

		// Pre-increment: Resume the coroutine to get the next element
		iterator& operator++()
		{
			handle_.resume();
			if (handle_.done())
			{
				handle_ = nullptr; // Mark as end
			}
			return *this;
		}

		// Equality comparison: Check if the coroutine has finished
		bool operator==(const iterator& other) const
		{
			return handle_ == other.handle_;
		}

	};

	// Range interface for 'for (const auto& p : generator)'
	iterator begin() const&
	{
		// Start the iterator, which will resume the coroutine once for the first element
		return iterator{ handle_ };
	}
	iterator begin() &&
	{
		// Start the iterator, which will resume the coroutine once for the first element
		return iterator{ handle_ };
	}
	
	iterator end() const&
	{
		// End iterator is a default-constructed one (nullptr handle)
		return iterator{};
	}
	iterator end() &&
	{
		// End iterator is a default-constructed one (nullptr handle)
		return iterator{};
	}

};

template <typename T>
typename Generator<T>::iterator begin(Generator<T>& gen) noexcept {
	return gen.begin();
}
template <typename T>
typename Generator<T>::iterator end(Generator<T>& gen) noexcept {
	return gen.end();
}

template <typename T>
typename Generator<T>::iterator begin(const Generator<T>& gen) noexcept {
	return gen.begin();
}
template <typename T>
typename Generator<T>::iterator end(const Generator<T>& gen) noexcept {
	return gen.end();
}

namespace std::ranges
{
	template <typename T>
	inline constexpr bool enable_borrowed_range<Generator<T>> = true;
}
