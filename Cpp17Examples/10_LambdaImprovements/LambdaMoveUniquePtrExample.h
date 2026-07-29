#pragma once
#include <functional>
#include <memory>
#include <string>

namespace LambdaImprovements
{
	class LambdaMoveUniquePtrExample
	{
	public:
		// C++17 can handle lambda, so use auto instead of using std::function<>
		// Note:
		// If use unique_ptr, the return value needs to be auto as lambda
		// Because if the return value is std::function<>,
		// it will run copy consructor when returning.
		// But unique_ptr can't be copied.
		// That's why these methods use "auto" instead of std::function<>
		// 
		//   (C2338 static_assert failed: 'The target function object type must be copy constructible')
		// 
		// And one more thing.
		// Definitions of methods returning auto needs to be written in .h file.
		// Because caller can include the h file, but the caller doesn't recognise what the "auto" supposed to be
		// So that's why declaration and definition needs to be writtein in .h file here.
		static auto createMessageLambda(const std::string& text)
		{
			auto message = std::make_unique<std::string>("Hello, " + text + "!");
			auto lambda = [msg = std::move(message)]() -> std::string
				{
					return *msg;
				};
			// when it is return as std::function<>, it would run copy constructor.
			// But it is not allowed because this method uses unique_ptr that can't be copied.
			// 
			return lambda;
		}
		static auto createIntProcessor(int baseValue)
		{
			auto ptr = std::make_unique<int>(baseValue);
			auto lambda = [p = std::move(ptr)]() -> int
				{
					return (*p) * 2;
				};
			return lambda;
		}

		static std::string executeMessageLambda();
		static int executeIntProcessor();
	};

	class LambdaMoveSharedPtrExample
	{
	public:
		// C++17 can handle lambda, so use auto instead of using std::function<>
		// Note:
		// In the case of shared_ptr, it can be copied.
		// So methods can return as std::function<>,
		// and method definitions can be writtein in .Cpp
		static std::function<std::string()> createMessageLambda(const std::string& text);
		static std::function<int()> createIntProcessor(int baseValue);
		static std::string executeMessageLambda();
		static int executeIntProcessor();
	};



}
