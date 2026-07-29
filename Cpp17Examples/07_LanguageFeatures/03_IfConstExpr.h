#pragma once
#include <type_traits>
#include <string>

namespace LanguageFeatures
{
	template<typename T>
	std::string TypeName()
	{
		// constexpr can work with type traits to determine type properties at compile time
		if constexpr (std::is_same_v<T, int>)
		{
			return "Integral";
		}
		else if constexpr (std::is_floating_point_v<T>)
		{
			return "Floating point";
		}
		else
		{
			return "Other";
		}
	}
}
