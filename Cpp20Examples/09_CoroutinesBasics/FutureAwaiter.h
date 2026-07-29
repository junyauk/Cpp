#pragma once
#include <coroutine>
#include <thread>
#include <iostream>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <future>


namespace FutureAwaiterSamples
{
	void EZLog(std::string msg)
	{
		std::stringstream ss;
		ss << "[TID:" << std::this_thread::get_id() << "] " << msg;
		std::cout << ss.str();
	}

	struct Task
	{
		struct promise_type
		{
			std::mutex m_mtx;
			std::condition_variable m_cv;
			bool m_finished{ false };

			Task get_return_object()
			{
				EZLog("Task::get_return_object enter.\n");
				auto ret = Task{ std::coroutine_handle<promise_type>::from_promise(*this) };
				EZLog("Task::get_return_object leave.\n");
				return ret;
			}
			std::suspend_always initial_suspend() const noexcept { return {}; }
			auto final_suspend() noexcept
			{
				struct Final
				{
					static bool await_ready() noexcept 
					{
						EZLog("Final::await_ready entered.\n");
						return false;
					}
					static void await_suspend(std::coroutine_handle<promise_type> h) noexcept
					{
						EZLog("Final::await_suspend -> enter.\n");
						auto& p = h.promise();
						{
							std::unique_lock ul(p.m_mtx);
							p.m_finished = true;
						}
						EZLog("Final::await_suspend before notify_all().\n");
						p.m_cv.notify_all();
						EZLog("Final::await_suspend after notify_all().\n");
						EZLog("Final::await_suspend <- leave.\n");
					}
					static void await_resume() noexcept
					{
						EZLog("Final::await_resume entered.\n");
					}
				};
				return Final{};
			}
			void return_void() {}
			void unhandled_exception() { std::terminate(); }
		};

		std::coroutine_handle<promise_type> m_h;

		explicit Task(std::coroutine_handle<promise_type> h) : m_h(h) {}
		~Task()
		{
			EZLog("~Task::~Task -> enter.\n");
			EZLog("~Task::~Task before calling destroy_safe().\n");
			if (m_h) destroy_safely();
			EZLog("~Task::~Task after calling destroy_safe().\n");
			EZLog("~Task::~Task <- leave.\n");
		}

		Task(const Task&) = delete;
		Task& operator=(const Task&) = delete;
		Task(Task&& o) noexcept : m_h(o.m_h) { o.m_h = {}; }
		Task& operator=(Task&& o) noexcept
		{
			EZLog("Task::operator= -> enter.\n");
			if (this != &o)
			{
				if (m_h) destroy_safely();
				m_h = o.m_h;
				o.m_h = {};
			}
			EZLog("Task::operator= <- leave.\n");
			return *this;
		}

		void start()
		{
			EZLog("Task::start -> enter.\n");
			if (m_h && !m_h.done())
			{
				EZLog("Task::start before calling m_h.resume.\n");
				m_h.resume();
				EZLog("Task::start after calling m_h.resume.\n");
			}
			EZLog("Task::start <- leave.\n");
		}
	private:
		void destroy_safely()
		{
			EZLog("Task::destroy_safely -> enter.\n");
			auto& p = m_h.promise();
			std::unique_lock ul(p.m_mtx);
			EZLog("Task::destroy_safely before wait.\n");
			p.m_cv.wait(ul, [&]() {return p.m_finished; });
			EZLog("Task::destroy_safely after wait.\n");
			ul.unlock();
			EZLog("Task::destroy_safely before destroy.\n");
			m_h.destroy();
			EZLog("Task::destroy_safely after destroy.\n");
			m_h = {};
			EZLog("Task::destroy_safely <- leave.\n");
		}
	};

	struct FutureAwaiter
	{
		std::shared_future<int> fut;

		bool await_ready() const noexcept
		{
			EZLog("~FutureAwaiter::await_ready -> enter.\n");
			auto ret = fut.wait_for(std::chrono::seconds(0));
			EZLog("~FutureAwaiter::await_ready <- leave.\n");
			return  ret == std::future_status::ready;
		}
		void await_suspend(std::coroutine_handle<> h)
		{
			EZLog("~FutureAwaiter::await_suspend -> before creating a thread.\n");
			std::thread([this, h]() mutable
				{
					fut.wait();
					h.resume();
				}).detach();
			EZLog("~FutureAwaiter::await_suspend <- after creating a thread.\n");
		}
		int await_resume()
		{
			EZLog("~FutureAwaiter::await_resume -> before fut.get().\n");
			auto ret = fut.get();
			EZLog("~FutureAwaiter::await_resume <- after fut.get().\n");
			return ret;
		}
	};

	Task asyncFunction()
	{
		EZLog("~asyncFunction -> start.\n");

		EZLog("~asyncFunction -> before creating a future.\n");
		std::shared_future<int> sf = std::async(std::launch::async, []
			{
				EZLog("Thread in asyncFunction's std::async -> enter.\n");
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
				EZLog("Thread in asyncFunction's std::async <- leave.\n");
				return 42;
			}).share();
		EZLog("~asyncFunction <- after creating a future.\n");

		EZLog("~asyncFunction -> before co_await.\n");
		int value = co_await FutureAwaiter{ sf };
		EZLog("~asyncFunction <- after co_await.\n");
		std::cout << "    result = " << value << "\n";

		EZLog("~asyncFunction <- exit.\n");
	}

}