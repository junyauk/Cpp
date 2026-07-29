#pragma once
#include <functional>
#include <memory>
#include <string>
#include <iostream>

namespace LambdaImprovements
{
	class LambdaFunctionOwnershipExample
	{
	public:
		// Note:
		// std::function<> can hold a copy constructible object only.
		// So this method will have a C2338 error
		// C2338 static_assert failed: 'The target function object type must be copy constructible (N4988 [func.wrap.func.con]/10.1).'
/*
		static std::function<void()> createFunctionWithMoveCapture()
		{
			auto resource = std::make_unique<std::string>("ResourceA");

			auto func = [resource = std::move(resource)]() mutable {
				*resource = "MoveCaptured";
				std::cout << "Executing with: " << *resource << std::endl;
				};

			return std::function<void()>( std::move(func) );
		}
*/
		static std::function<void()> createFunctionWithSharedCapture()
		{
			auto ptr = std::make_shared<std::string>("SharedCaptured");
			return [p = ptr]() // Copying the shared pointer
				{
					std::cout << "Executing with: " << *p << std::endl;
				};
		}

		static bool isCopyConstructibleTest()
		{
			auto ptr = std::make_unique<int>(5);
			auto moveOnlyLambda = [p = std::move(ptr)]() { std::cout << *p << std::endl; };
			return std::is_copy_constructible_v<decltype(moveOnlyLambda)>;
		}
	};


}

