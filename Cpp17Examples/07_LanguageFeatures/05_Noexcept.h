#pragma once
#include <type_traits>

namespace LanguageFeatures
{
	template<typename T>
	void MightThrow() noexcept(std::is_integral_v<T>)
	{
		if constexpr (!std::is_integral_v<T>)
		{
			throw "Only integral types are noexcept!";
		}
	}
}
