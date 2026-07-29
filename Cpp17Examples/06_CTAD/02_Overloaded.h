#pragma once
#include <string>
#include <iostream>
#include <variant>

namespace CTADExample2
{
	// overloaded struct for std::visit
	template<class... Ts>
	struct Overloaded : Ts... { using Ts::operator()...; };
	// CTAD(Class Template Argument Deduction) for Overloaded
	template<class... Ts>
	Overloaded(Ts...) -> Overloaded<Ts...>;

	inline void example()
	{
		std::variant<int, std::string, bool> v = 42;

		auto visitor = Overloaded
			{
				[](int arg) { std::cout << "int: " << arg << "\n"; },
				[](const std::string& arg) { std::cout << "string: " << arg << "\n"; },
				[](bool arg) { std::cout << "bool: " << (arg ? "true" : "false") << "\n"; }
			};

		std::visit(visitor, v);

		v = std::string("hello");
		std::visit(visitor, v);

		v = true;
		std::visit(visitor, v);
	}
}
