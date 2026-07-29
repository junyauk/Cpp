#pragma once

namespace LanguageFeatures
{

	[[maybe_unused]] inline void UnusedFunction() {}

	inline void MaybeUnusedExample()
	{
		[[maybe_unused]] int x = 42; // x might be unused
		[[maybe_unused]] auto lambda = []() { return 100; }; // lambda might be unused
		// Uncommenting the following line will use 'x' and 'lambda'
		// std::cout << "x: " << x << ", lambda(): " << lambda() << "\n";
	}
}
