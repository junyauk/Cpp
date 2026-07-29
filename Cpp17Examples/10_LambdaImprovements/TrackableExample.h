#pragma once
#include <tuple>
#include <string>

namespace LambdaImprovements
{
	class Trackable
	{
	public:
		inline static int copyCount = 0;
		inline static int moveCount = 0;

		std::string name;

		Trackable(std::string s) : name(std::move(s)) {}

		Trackable(const Trackable& other) noexcept : name(other.name)
		{
			++copyCount;
		}
		Trackable(Trackable&& other) noexcept : name(std::move(other.name))
		{
			++moveCount;
		}

		static void resetCounters()
		{
			copyCount = 0;
			moveCount = 0;
		}
	};

	class TrackableExample
	{
	public:
		static std::tuple<Trackable> makeTupleByCopy(const Trackable& t)
		{
			return std::make_tuple(t);
		}

		static std::tuple<Trackable> makeTupleByMove(Trackable&& t)
		{
			return std::make_tuple(std::move(t));
		}
	};

}

