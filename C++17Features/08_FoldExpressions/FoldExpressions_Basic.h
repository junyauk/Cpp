#pragma once
#include <string>
#include <sstream>

namespace FOLDEXPRESSIONS_Basic
{
	class FoldExpressions_Basic
	{
	public:
		// 1. Unary Left Fold: Simple Summation
		// Calculates the sum of all passed arguments.
		template<typename... Args>
		auto sumAll(Args... args) const;

		// 2. Binary Right Fold: Stream Concatenation
		// Concatenates all arguments into a single string stream, starting with 'init'.
		template<typename T, typename... Args>
		std::string concatnate(T init, Args... args) const;

		// 3. Unary Right Fold: Logical AND Check
		// Checks if all passed boolean arguments are true.
		template<typename... Bools>
		bool allTrue(Bools... args) const;
	};

	// =========================================================================
	// Template Implementations (must be in header for separate compilation)
	// =========================================================================

	// 1. Unary Left Fold (no initial value)
	template<typename... Args>
	auto FoldExpressions_Basic::sumAll(Args... args) const
	{
		// Equivalent to: (((arg1 + arg2) + arg3) + ...)
		// Requires that the parameter pack is non-empty.
		// If args is empty, this is ill-formed unless a special case for zero arguments is defined (not shown here for simplicity).
		return (args + ...);
	}

	// 2. Binary Right Fold (with initial value)
	template<typename T, typename... Args>
	std::string FoldExpressions_Basic::concatnate(T init, Args... args) const
	{
		std::stringstream ss;
		ss << init;	// Start with the initial value

		// Binary right fold using the comma operator: 
		// (ss << arg1, ss << arg2, ...)
		// The result of the comma operator is the result of the right operand, but here we discard the result
		// as the side effect (ss << ...) is what matters.
		// We ensure all arguments are processed by wrapping the stream operation in the fold.
		// Note: For std::ostream operations, a cleaner binary left fold often suffices: (ss << init << ... << args)
		// Let's stick to the common stream fold pattern:
		// (void) ensures that the result of the fold expression is discarded if necessary.
		(void)((ss << " : " << args), ...);

		return ss.str();
	}

	// 3. Unary Right Fold (Logical AND)
	template<typename... Bools>
	bool FoldExpressions_Basic::allTrue(Bools... args) const
	{
		// Equivalent to: (arg1 && (arg2 && (arg3 && ...)))
		// This is a unary right fold over the '&&' operator.
		// The empty pack case for '&&' evaluates to 'true'.
		return (args && ...);
	}
}

