#pragma once
#include <string>
#include <iostream>

namespace CTADExample1
{
	template<typename T1, typename T2>
	class MyPair
	{
	public:
		T1 first;
		T2 second;
		MyPair(const T1& f, const T2& s) : first(f), second(s) {}
	};

	// Deduction guide
	template<typename T1, typename T2>
	MyPair(const T1&, const T2&) -> MyPair<T1, T2>;
}
