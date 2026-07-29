#pragma once
#include <functional>
#include <string>

namespace LambdaImprovements
{
	class LambdaVsBindExample
	{
	public:
		static int multiply(int a, int b);

		static std::function<int(int)> createBindMultiplier(int factor);
		static std::function<int(int)> createLambdaMultiplier(int factor);

		static std::function<std::string()> createBindStringAppender(std::string text);
		static std::function<std::string()> createLambdaStringAppender(std::string text);
	};
}
