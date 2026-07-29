#pragma once
#include <coroutine>
#include <iostream>
#include <exception>
#include <optional>
#include <thread>
#include "TimerQueue.h"

template<typename T>
struct Task;

// ----------------------------------------------------
// 1. Promise Type (Holds coroutine state and result)
// ----------------------------------------------------
template<typename T>
struct TaskPromise
{
	using Handle = std::coroutine_handle<TaskPromise>;

	T result_;	// Store the value returned by co_return

	// NOTE:
	// This is for nested tasks.
	// This is the caller (parent task)'s handle.
	std::coroutine_handle<> continuation_handle;

	// Exception
	std::exception_ptr exception_ptr_;

	// 1.1. Action when the coroutine is first caled
	auto get_return_object()
	{
		return Task<T>{Handle::from_promise(*this)};
	}

	// 1.2. Initial suspend (suspends before execution starts)
	auto initial_suspend() noexcept { return std::suspend_always{}; }
	// 1.3. Final suspend (action after co_return)
	auto final_suspend() noexcept 
	{ 
		struct FinalAwaiter
		{
			bool await_ready() const noexcept { return false; }
			void await_suspend(Handle h) const noexcept
			{
				if (h.promise().continuation_handle)
				{
					// Resume the parent's coroutine.
					h.promise().continuation_handle.resume();
					// Destroy the child's coroutine
					h.destroy();
				}

			}
			void await_resume() const noexcept {}
		};
		return FinalAwaiter{};
	}
	// 1.4. Processing for co_return T;
	void return_value(T value)
	{
		result_ = std::move(value); 
	}
	// 1.5. Exception handling
	void unhandled_exception()
	{
		//		std::terminate();
		exception_ptr_ = std::current_exception();
	}

	// Getter for Task to retrieve the result
	T get_result()
	{
		if (exception_ptr_)
		{
			std::rethrow_exception(exception_ptr_);
		}

		return std::move(result_);
	}
};

// ----------------------------------------------------
// 2. Task Class (Wrapper holding the coroutine handle)
// ----------------------------------------------------
template<typename T>
struct Task
{
	using promise_type = TaskPromise<T>;
	using Handle = std::coroutine_handle<promise_type>;

	Handle handle_;

	// Constructor accepting the Handle (called from promise_type)
	Task(Handle h) : handle_(h)
	{
		std::cout << "Task constructor\n";
	}

	// Move semantics (transfer ownership)
	Task(Task&& other) noexcept : handle_(std::exchange(other.handle_, nullptr))
	{
		std::cout << "Task copy constructor\n";
	}
	~Task()
	{
		if (handle_)
		{
			handle_.destroy();
		}
	}

	// Starts/resumes the task and gets the result
	T start_and_get_result()
	{
		if (!handle_) return T{};

		handle_.resume();


		while (!handle_.done())
		{
//			handle_.resume();
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}

		return handle_.promise().get_result();
	}

	// NOTE: Actual async tasks require await_transform methods for co_await,
	// but this is minimal for co_return demonstration.

	/**
	 * @brief Allows 'co_await task_object;' syntax.
	 * This makes the Task itself satisfy the Awaitable requirements.
	 */
	auto operator co_await() && noexcept
	{
		std::cout << "Task's co_await() operator\n";
		struct TaskAwaiter
		{
			Handle handle;

			// 1. Ready? Always false to suspend and execute the child task.
			bool await_ready() const noexcept
			{
				return false;
			}

			// 2. Suspend: Resumes the child task, and sets up continuation.
			//    MUST return true to suspend the caller (parent task).
			bool await_suspend(std::coroutine_handle<> caller) const noexcept
			{
				// 1. Set the caller (parent coroutine) 's handle to the promise.
				//    It will be resumed when the child coroutine terminate at co_return.
				handle.promise().continuation_handle = caller;
				// 2. Execute the child task we are waiting
				handle.resume();

				return true;
			}

			// 3. Resume: Returns the actual result stored in the task's promise.
			T await_resume() const noexcept
			{
				T result = handle.promise().get_result();

				return result;
			}
		};
//		return TaskAwaiter{ handle_ }; // This is not enough, handle_ needs to be null cleared.
		return TaskAwaiter{ std::exchange(handle_, nullptr) };
	}

	void release_handle() noexcept
	{
		handle_ = nullptr;
	}
};

/**
 * @brief Simple Awaiter to simulate a non-blocking delay.
 */
struct DelayAwaiter
{
	int milliseconds;

	// 1. ready? (Always false to force suspension for demonstration)
	bool await_ready() const noexcept { return false; }

	// 2. What to do when suspending?
	void await_suspend(std::coroutine_handle<> handle) const noexcept
	{
		// In a real scenario, we would register this handle to an event loop or timer.
		// For simulation, we manually resume it to mimic a completion event.
		std::cout << "    [Awaiter] Suspending for " << milliseconds << "ms...\n";

		get_timer_queue().add_timer(handle, milliseconds);
		// Simulating completion by immediately resuming (in a real app, this happens later)
		handle.resume();

	}

	// 3. What to return after resumption?
	void await_resume() const noexcept
	{
		std::cout << "    [Awaiter] Resumed.\n";
	}
};

