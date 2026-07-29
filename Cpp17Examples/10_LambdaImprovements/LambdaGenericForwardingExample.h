#pragma once
#include <memory>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <functional>
#include <type_traits>

namespace LambdaImprovements
{
	// 1. Typical lambda
	class GenericLambdaExample
	{
	public:
		static std::vector<std::string> demonstrate()
		{
			std::vector<std::string> results;

			// this lambda can treat both int and string
			auto printer = [](auto value) // Since C++14, "auto" can be used for parameters
				{
					std::ostringstream oss;
					oss << value;
					return oss.str();
				};
			results.push_back(printer(42));
			results.push_back(printer(std::string("Hello")));
			results.push_back(printer(3.14));
			return results;
		}
	};

	// 2. Forwarding lambda
	class ForwardingLambdaExample
	{
	public:
		// This is the wrapper
		template<typename Func, typename... Args>
		static auto invoke(Func&& func, Args&&... args)
		{
			// Using std::forward keeps lvalue/rvalue attribute
			return std::forward<Func>(func)(std::forward<Args>(args)...);
		}

		static std::string demonstrate()
		{
			auto concat = [](auto&& a, auto&& b)
				{
					std::ostringstream oss;
					oss << a << b;
					return oss.str();
				};
			std::string s1 = "Hello";
			std::string s2 = "World";

			// lvalue + rvalue mixed
			auto result = invoke(concat, s1, std::move(s2));
			return result;
		}
	};

	// 3. Generic event dispatcher
	class EventDispatcher
	{
	private:
		std::vector<std::function<void()>> m_handlers;
	public:
		template<typename F, typename... Args>
		void addHandler(F&& func, Args... args)
		{
			m_handlers.emplace_back(
				[=]()mutable {std::forward<F>(func)(std::forward<Args>(args)...); }
			);
		}

		void dispatchAll()
		{
			for (auto& h : m_handlers)
			{
				h();
			}
		}
	};

}
