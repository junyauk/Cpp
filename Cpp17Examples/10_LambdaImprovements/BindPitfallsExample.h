#pragma once
#include <functional>
#include <string>


namespace LambdaImprovements
{
	class BindPitfallsExample
	{
	public:
		static std::function<int(int, int)> wrongOrderBind();

		static std::function<void()> danglingReferenceBind();
		static std::function<int(int, int)> correctOrderLambda();
		static std::function<void()> safeLambda();
	};
}
