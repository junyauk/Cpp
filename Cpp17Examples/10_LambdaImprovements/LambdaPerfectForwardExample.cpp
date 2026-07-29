#include "pch.h"
#include <sstream>
#include <iostream>
#include <utility>
#include "LambdaPerfectForwardExample.h"

namespace LambdaImprovements
{
	struct Tracker
	{
		std::string name;
		static inline int copyCount = 0;
		static inline int moveCount = 0;

		Tracker(std::string n) : name(std::move(n)) {}
		Tracker(const Tracker& other) noexcept :name(other.name)
		{
			++copyCount;
		}
		Tracker(Tracker&& other) noexcept :name(std::move(other.name))
		{
			++moveCount;
		}
		static void resetCounters()
		{
			copyCount = 0;
			moveCount = 0;
		}
	};

	std::string LambdaPerfectForwardExample::compareCopyAndPerfectForward()
	{
		std::ostringstream oss;
		Tracker::resetCounters();
		Tracker t("ItemA");

		auto copyLambda = [](auto x)
			{
				return x.name + "_copied";
			};
		copyLambda(t);
		oss << "CopyLambda - Copies: " << Tracker::copyCount << ", Moves: " << Tracker::moveCount << std::endl;
		Tracker::resetCounters();

		// Note:
		// T&& : It will accept rvalue only
		// auto&& : It will accept BOTH lvalue & rvalue
		auto forwardLambda = [](auto&& x) -> std::string // so thos lambda will accept BOTH lvalue and rvalue
			{
				// decltype(x) : return type with lvalue or rvalue
				// std::forward<type>(x) : forwarding x in the specified type
				auto y = std::forward<decltype(x)>(x);
				return y.name + "_forwarded";
			};
		forwardLambda(Tracker("Temp"));
		oss << "ForwardLambda - Copies: " << Tracker::copyCount << ", Moves: " << Tracker::moveCount << std::endl;

		return oss.str();
	}
}

