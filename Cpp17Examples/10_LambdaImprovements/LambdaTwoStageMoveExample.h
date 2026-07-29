#pragma once
#include <memory>
#include <iostream>
#include <string>
#include <functional>

namespace LambdaImprovements
{
	// Note:
	// mutable
	// You can use "mutable" if you want to modify the parameters in [] in lambda
	/*
		auto ptr = std::make_unique<int>(42);

		// NG
		auto f = [p = std::move(ptr)]() // "ptr" is moved
		{
			// The "p" is const unique_ptr in this lamba implicitly
			auto q = std::move(p); // Error: const unique_ptr can't be moded !!!
		};
		// OK
		auto f = [p = std::move(ptr)]() mutable
		{
			auto q = std::move(p);		// OK, "p" can be moved because "p" can be modified
			std::cout << (q ? *q : 0) << std::endl;
		};
	*/

	class TwoStageMoveExample
	{
	public:
		static void run()
		{
			// Step1:
			auto ptr = std::make_unique<int>(42);
			std::cout << "[Step1] ptr owner? " << (ptr ? "Available" : "Not available") << std::endl;

			// Step2:
			// Note:
			// "mutable" allows the function modify the copied parameter "p" in []
			auto firstLambda = [p = std::move(ptr)]() mutable
				{
					std::cout << "[Step2] In the firstLambda: p= "
						<< (p ? std::to_string(*p) : "null") << std::endl;
					auto secondLambda = [q = std::move(p)]() mutable
						{
							std::cout << "[Step3] in the secondLambda: q="
								<< (q ? std::to_string(*q) : "null") << std::endl;
						};

					std::cout << "[Step1] p has been moved to the secondLambda.\n";
					secondLambda();
					std::cout << "[Step2] p="
						<< (p ? std::to_string(*p) : "null") << std::endl;
				};
			std::cout << "[Step1] ptr has been moved to the firstLambda.\n";
			firstLambda();
		}
	};
}

