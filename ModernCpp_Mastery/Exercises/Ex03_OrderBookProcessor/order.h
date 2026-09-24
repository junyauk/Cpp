#pragma once
#include <concepts>

namespace Ex03_OrderBookProcessor
{
	enum Side
	{
		BUY,
		SELL
	};

	enum OrderType
	{
		LIMIT,
		MARKET
	};

	enum Action
	{
		ADD,
		MODIFY,
		CANCEL
	};

	template<typename T>
	concept EssentialFields = requires(T o)
	{
		{ o.orderId } -> std::convertible_to<uint64_t>;
		{ o.timestamp } -> std::convertible_to<uint64_t>;
		{ o.symbolId } -> std::convertible_to<uint32_t>;
		{ o.price } -> std::convertible_to<uint32_t>;
		{ o.quantity } -> std::convertible_to<uint32_t>;
#if 1 // directly check if convertible
		{ o.side } -> std::convertible_to<Side>;
		{ o.type } -> std::convertible_to<OrderType>;
		{ o.action } -> std::convertible_to<Action>;
#else // using remove_cvref_t for removing const, volatile and reference, and using same_as for comparing the type
		requires std::same_as<std::remove_cvref_t<decltype(o.side)>, Side>;
		requires std::same_as<std::remove_cvref_t<decltype(o.type)>, OrderType>;
		requires std::same_as<std::remove_cvref_t<decltype(o.action)>, Action>;
#endif
		requires std::totally_ordered<decltype(o.price)>;
		requires std::totally_ordered<decltype(o.quantity)>;
	};

	template<typename T>
	concept Copyable = std::is_trivially_copyable_v<T>;

	template<typename T>
	concept FitInCacheLine = (sizeof(T) <= 64) && (alignof(T) <= 64);

	template<typename T>
	concept OrderCompatible = EssentialFields<T> && Copyable<T> && FitInCacheLine<T>;

	struct Order
	{
		uint64_t orderId;
		uint64_t timestamp;
		uint32_t symbolId;
		uint32_t price;
		uint32_t quantity;
		Side side;
		OrderType type;
		Action action;
	};
}
