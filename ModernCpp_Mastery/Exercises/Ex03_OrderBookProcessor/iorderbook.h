#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>
#include <deque>
#include <map>
#include <unordered_map>
#include <chrono>
#include <algorithm>
#include <optional>
#include <Windows.h>
#include "Order.h"
#include "criticalsection.h"

namespace Ex03_OrderBookProcessor
{
	template<OrderCompatible T>
	class IOrderBook
	{
	public:
		virtual ~IOrderBook() = default;

		virtual void Add(const T order) = 0;
		virtual bool Modify(const T order) = 0;
		virtual bool Cancel(const T order) = 0;
		virtual std::optional<T> GetBestBid() const = 0;
		virtual std::optional<T> GetBestAsk() const = 0;
	};
}
