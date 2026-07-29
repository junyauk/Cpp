#pragma once
#include <coroutine>
#include <optional>
#include <iostream>

// ------------------------------------------------------------------------
namespace CoroutineSamples
{
	struct SimpleTask
	{
		struct promise_type // 0: This struct's instance will be created first
		{
			SimpleTask get_return_object() // 1: This function will be called for returning the instance
			{
				// 2: return the instance
				return SimpleTask{ std::coroutine_handle<promise_type>::from_promise(*this) };
			}
			// 3: After the instance was returned, initial_suspend is called
			std::suspend_always initial_suspend() { return {}; }
			std::suspend_always final_suspend() noexcept { return {}; }
			void return_void() {}
			void unhandled_exception() { std::terminate(); }
		};


		// - Essentials --------------------------------
		// The handle
		std::coroutine_handle<promise_type> handle;
		// Constructor for setting coroutine_handle
		SimpleTask(std::coroutine_handle<promise_type> h) : handle(h) {}
		// Destructor for calling destroy
		~SimpleTask() { if (handle) handle.destroy(); }
	};

	SimpleTask simpleCoroutine()
	{
		std::cout << "Step 1" << std::endl;
		co_await std::suspend_always{};
		std::cout << "Step 2" << std::endl;
	}
#if 0 // how coroutine instance is created actually
	SimpleTask simpleCoroutine() {
		// 1. promise の生成
		SimpleTask::promise_type promise;

		// 2. return object を取得
		SimpleTask task = promise.get_return_object();

		// 3. initial_suspend を確認
		auto init = promise.initial_suspend();
		if (init.await_ready() == false) {
			// suspend → 実際にはハンドルの状態にセットされる
		}

		// 4. 本体を実行する準備が整う（resume呼び出しで "Step 1" から進む）

		return task;
	}
#endif
}
