#pragma once
#include <variant>
#include <memory>

namespace ExpressionVariantExamples
{
	struct Number
	{
		double value;
	};

	struct Add;
	struct Mul;

	using Expr = std::variant<Number, std::shared_ptr<Add>, std::shared_ptr<Mul>>;

	struct Add
	{
		Expr lhs, rhs;
	};

	struct Mul
	{
		Expr lhs, rhs;
	};

	inline double eval(const Expr& expr)
	{
		return std::visit(
			[](auto&& node) -> double
			{
				using T = std::decay_t<decltype(node)>;
				if constexpr (std::is_same_v<T, Number>)
				{
					return node.value;
				}
				else if constexpr (std::is_same_v<T, std::shared_ptr<Add>>)
				{
					return eval(node->lhs) + eval(node->rhs);
				}
				else if constexpr (std::is_same_v<T, std::shared_ptr<Mul>>)
				{
					return eval(node->lhs) * eval(node->rhs);
				}
			}, expr);
	}
}

