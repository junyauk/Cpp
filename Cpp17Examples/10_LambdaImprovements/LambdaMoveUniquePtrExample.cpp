#include "pch.h"
#include "LambdaMoveUniquePtrExample.h"

namespace LambdaImprovements
{
	// ---------------------------------------------------------------------------
	// Using unique_ptr
	// Note:
	// The following methods returning "auto" can't be written in Cpp.
	// Caller needs to know what the "auto" supposed to be actually.
//	auto createMessageLambda(const std::string& text)
//	auto createIntProcessor(int baseValue)

	std::string LambdaMoveUniquePtrExample::executeMessageLambda()
	{
		auto lambda = createMessageLambda("Lambda");
		return lambda();
	}

	int LambdaMoveUniquePtrExample::executeIntProcessor()
	{
		auto lambda = createIntProcessor(10);
		return lambda();
	}

	// ---------------------------------------------------------------------------
	// Using shared_ptr
	// Note:
	// Methods returning "std::function<>" can be written in Cpp.
	std::function<std::string()> LambdaMoveSharedPtrExample::createMessageLambda(const std::string& text)
	{
		auto message = std::make_shared<std::string>("Hello, " + text + "!");
		auto lambda = [msg = std::move(message)]() -> std::string
			{
				return *msg;
			};
		return lambda;
	}
	std::function<int()> LambdaMoveSharedPtrExample::createIntProcessor(int baseValue)
	{
		auto ptr = std::make_shared<int>(baseValue);
		auto lambda = [p = std::move(ptr)]() -> int
			{
				return (*p) * 2;
			};
		return lambda;
	}

	std::string LambdaMoveSharedPtrExample::executeMessageLambda()
	{
		auto lambda = createMessageLambda("Lambda");
		return lambda();
	}

	int LambdaMoveSharedPtrExample::executeIntProcessor()
	{
		auto lambda = createIntProcessor(10);
		return lambda();
	}
}
