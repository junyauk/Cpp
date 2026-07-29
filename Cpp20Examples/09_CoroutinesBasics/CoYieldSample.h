#pragma once
#include <coroutine>
#include <future>
#include <chrono>
#include <thread>
#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

namespace CoYieldSample
{
	void EZLog(std::string str)
	{
		std::stringstream ss;
		ss << "[TID:" << std::this_thread::get_id() << "] " << str;
		std::cout << ss.str();
	}

	template <typename T>
	struct Generator
	{
		struct promise_type
		{
			T m_value;
			Generator get_return_object()
			{
				return Generator{ std::coroutine_handle<promise_type>::from_promise(*this) };
			}
			std::suspend_always initial_suspend() const noexcept { return{}; }
			std::suspend_always final_suspend() const noexcept { return{}; }
			std::suspend_always yield_value(T value)
			{
				m_value = value;
				return {};
			}
			void return_void() const noexcept {}
			void unhandled_exception() { std::current_exception(); }
		};

		using handle_type = std::coroutine_handle<promise_type>;
		handle_type m_h;

		Generator(handle_type h) : m_h(h) {}

		Generator(const Generator&) = delete;
		Generator& operator=(const Generator&) = delete;

		Generator(Generator&& o) noexcept : m_h(o.m_h) { o.m_h = {}; }
		Generator& operator=(Generator&& o)
		{
			if (m_h)
			{
				m_h.destroy();
			}
			m_h = std::move(o.m_h);
		}

		~Generator()
		{
			if (m_h)
			{
				m_h.destroy();
			}
		}

		struct Iterator
		{
			std::coroutine_handle<promise_type> m_h;

			Iterator& operator++()
			{
				if (m_h && !m_h.done())
				{
					m_h.resume();
				}
				
				if (m_h && m_h.done())
				{
					m_h = nullptr;
				}
				return *this;
			}

			T operator*() const
			{
				return m_h.promise().m_value;
			}

			bool operator!= (const Iterator& other) const
			{
				return m_h != other.m_h;
			}

			bool operator==(const Iterator& other) const
			{
				return m_h == other.m_h;
			}
		};

		Iterator begin()
		{
			if (!m_h)
			{
				return end();
			}
			m_h.resume();
			if (m_h.done())
			{
				return end();
			}
			return Iterator{ m_h };
		}

		Iterator end()
		{
			return Iterator{ nullptr };
		}
	};

	Generator<int> fibonacci_genrator()
	{
		int a = 0, b = 1;
		while (true)
		{
			co_yield a;
			int next = a + b;
			a = b;
			b = next;
		}
	}

	Generator<std::string> read_lines_from_csv(const std::string& filename)
	{
		std::ifstream file(filename);
		if (!file.is_open())
		{
			std::cerr << "Could not open file: " << filename << std::endl;
			co_return;
		}

		std::string line;
		while (std::getline(file, line))
		{
			co_yield line;
		}
	}

	template<typename Container>
	Generator<typename Container::value_type> flatten(const std::vector<Container>& containers)
	{
		for (const auto& container : containers)
		{
			for (const auto& item : container)
			{
				co_yield item;
			}
		}
	}
}