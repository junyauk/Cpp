#pragma once
#include <string>
#include <vector>
#include <numeric>
#include <utility>

namespace LambdaImprovementsExamples
{
	class LambdaImprovements
	{
	public:
		static int basicLambda(int a, int b)
		{
			auto add = [](int x, int y) {return x + y; };
			return add(a, b);
		}

		static int genericLambda(int a, int b)
		{
			auto mul = [](auto x, auto y) { return x * y; };
			return mul(a, b);
		}

		static std::string initCapture(const std::string& str)
		{
			auto f = [msg = str]()
				{
					return msg + " world";
				};
			return f();
		}

		static constexpr int constexprLambda(const int n)
		{
			auto square = [](int x) constexpr
				{
					return x * x;
				};
			return square(n);
		}

		struct Wrapper
		{
			int value{ 0 };
			auto makeLambda()
			{
				return [=]() {return value * 2; };
			}
		};

		static int captureThis()
		{
			Wrapper w{ 10 };
			auto f = w.makeLambda();
			return f();
		}

		struct RefLambda
		{
			int counter{ 0 };
			auto get()& // for lvalue call
			{
				return [this]() {return counter++; };
			}
			auto get()&& // for rvalue call
			{
				return [val = counter]() {return val * 2; };
			}
		};

		static int refQualifiedLambda()
		{
			RefLambda rl{ 5 };
			auto f1 = rl.get(); // for lvalue
			auto f2 = RefLambda{ 10 }.get(); // for rvalue
			return f1() + f2(); // 5 + (10 * 2)
		}
	};
}

