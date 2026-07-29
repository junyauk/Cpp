#pragma once
#include <functional>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

namespace LambdaImprovements
{
	class LambdaFunctionComparison
	{
	public:
		struct Counter
		{
			int value;
			explicit Counter(int v) : value(v){}
			Counter(const Counter& other) : value(other.value)
			{
				++copyCount;
			}
			static inline int copyCount = 0;
		};

		static std::string functionCopyBehaviorDetailed()
		{
			Counter::copyCount = 0;
			Counter c(0);

			auto lambda = [c]() mutable {return ++(c.value); };

			std::ostringstream oss;
			oss << "after lambda creation, copyCount=" << Counter::copyCount;

			std::function<int()> f1 = lambda;
			std::function<int()> f2 = lambda;

			oss << ", after assigning to std::function, copyCount=" << Counter::copyCount;

			int result = f1() + f2();

			oss << ", result=" << result;
			return oss.str();
		}

		static std::string inspectClosure()
		{
			int x = 10;
			int y = 20;

			auto lambda = [x, &y]() { return x + y; };

			y += 5;

			int result = lambda();

			std::ostringstream oss;
			oss << "x=10(y by ref), result=" << result;
			return oss.str();
		}

		static int usingStdFunction()
		{
			int factor = 3;
			std::function<int(int)> multiply = [factor](int v) {return v * factor; };
			return multiply(5);
		}

		static int functionCopyBehavior()
		{
			int counter = 0;
			auto lambda = [counter]() mutable {return ++counter; };
			std::function<int()> f1 = lambda;
			std::function<int()> f2 = lambda;

			// counter is copied when lambda is created
			return f1() + f2(); // (1 + 1) = 2
		}

		static std::string typeDifference()
		{
			auto lambda = [](int a, int b) {return a + b; };
			std::function<int(int, int)> func = lambda;

			std::ostringstream oss;
			oss << "lambda type: " << typeid(lambda).name()
				<< "\nstd::function type: " << typeid(func).name();
			return oss.str();
		}
	};
}