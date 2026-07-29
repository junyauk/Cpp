#pragma once
#include <string>
#include <vector>

namespace LanguageFeatures
{
	// "inline" can be used in h files to avoid multiple definition errors.
	// it means this variable has the same instance across translation units.
	// Without "inline", each translation unit including this header will have its own instance.
	// This is useful for global constants or counters.
	// Note: "const" variables have internal linkage by default, so they don't need "inline".
	// However, non-const globals should use "inline" to avoid linker errors.
	// Example usage:
	// LanguageFeatures::GlobalCounter++;
	// std::cout << LanguageFeatures::GlobalCounter << std::endl;
	// This variable will be shared across all .cpp files including this header.
	// If "inline" is omitted, you will get a linker error about multiple definitions.
	inline int GlobalCounter = 0;

	struct Config
	{
		inline static int MaxValue = 100; // static variable in class can be inline

		inline static int sharedValue = 0;
	};

	// Each cpp will have individual ones
	static int staticCounter = 0;

	// It will be shared by all Cpp
	inline int inlineCounter = 0;

	void incrementA();
	void incrementB();
	void incrementC();
	std::vector<int> getCountersA();
	std::vector<int> getCountersB();
	std::vector<int> getCountersC();

	std::string reportValues();
}

