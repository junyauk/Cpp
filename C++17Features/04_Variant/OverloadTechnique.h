#pragma once
#include <variant>
#include <string>
#include <iostream>

namespace OverloadTechniqueExamples
{
	template<class... Ts>
	struct overload : Ts... // Ts...: Inherit multiple classes
	{
		using Ts::operator()...; // Overload all operator() of multiple classes
	};

	template<class... Ts>
	overload(Ts...) -> overload<Ts...>; // The overload accepts multiple lambda functions


	using InputType = std::variant<int, double, std::string>;
	using ReturnType = std::variant<std::monostate, int, double, std::string>;

	std::string UsingIndexAndGet(const InputType& v);
	std::string UsingGetIf(const InputType& v);
	std::string UsingHoldsAlternative(const InputType& v);
	std::string UsingVisitWithSingleLambdaAndConstexpr(const InputType& v);
	std::string UsingVisitWithFunctor(const InputType& v);

	void OverloadTechnique_NoReturn();
	void OverloadTechnique_SameTypeReturn();
	void OverloadTechnique_VariousTypeReturn();
	void OverloadTechnique_ContainVoidReturn();
}
