#pragma once
#include <string>
#include <variant>
#include <iostream>

namespace CTADExample3
{
	// MoveOnly type
	struct MoveOnly
	{
		std::string data;
		MoveOnly(std::string d) : data(std::move(d)) {}
		// copy constructor deleted
		MoveOnly(const MoveOnly&) = default;
		MoveOnly& operator=(const MoveOnly&) = default;
		// move constructor
		MoveOnly(MoveOnly&& other) noexcept : data(std::move(other.data)) {}
		MoveOnly& operator=(MoveOnly&& other) noexcept
		{
			if (this != &other)
			{
				data = std::move(other.data);
			}
			return *this;
		}
	};

	// Helper for std::visit with multiple lambdas
	template<class...Ts>
	struct Overloaded : Ts... { using Ts::operator()...; };
	// CTAD(Class Template Argument Deduction) for Overloaded
	template<class... Ts>
	Overloaded(Ts...) -> Overloaded<Ts...>;

	inline void example()
	{
		std::variant<int, MoveOnly> v = MoveOnly("init");
		auto visitor = Overloaded
		{
			[](int arg) { std::cout << "int: " << arg << "\n"; },
			[](const MoveOnly& arg) { std::cout << "MoveOnly: " << arg.data << "\n"; }
		};

		std::visit(visitor, v);

		v = MoveOnly("moved data");
		std::visit(visitor, v);

		v = 100;
		std::visit(visitor, v);
	}
}
