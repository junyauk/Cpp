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
#include "order.h"
#include "iorderbook.h"
#include "criticalsection.h"

namespace Ex03_OrderBookProcessor
{
	template<OrderCompatible T>
	class ClassicOrderBook : public IOrderBook<T>
	{
	public:
		ClassicOrderBook(uint32_t symbolId) : m_symbolId(symbolId) {}
		~ClassicOrderBook() {}

		ClassicOrderBook() = delete;
		ClassicOrderBook(const ClassicOrderBook&) = delete;
		ClassicOrderBook(ClassicOrderBook&&) = delete;
		ClassicOrderBook& operator=(const ClassicOrderBook&) = delete;
		ClassicOrderBook& operator=(ClassicOrderBook&&) = delete;

		void Add(const T order) override
		{
			// Check if it's a valid order
			if (!IsValidOrder(order) || order.action != ADD) return;

			CS cs(m_cs);

			// Add order
			AddOrder(order);
		}
		bool Modify(const T order) override
		{
			// Check if it's a valid order
			if (!IsValidOrder(order) || order.action != MODIFY) return false;

			CS cs(m_cs);

			auto it = m_orders.find(order.orderId);
			// it.first : orderId
			// it.second.first : price
			// it.second.second : iterator to deque
			if (it == m_orders.end())
			{
				return false;
			}

			T& oldOrder = *(it->second.it);

			// Check if .Cancel() and .Add() is needed or in-place modification is possible
			if (IsInplaceModifiable(oldOrder, order))
			{
				// Update the order in place
				ModifyOrder(oldOrder, order);
			}
			else
			{
				// Remove the order from the old price level
				CancelOrder(order.orderId);
				// Add the order to the new price level
				AddOrder(order);
			}
			return true;
		}
		bool Cancel(const T order) override
		{
			// Check if it's a valid order
			if (!IsValidOrder(order) || order.action != CANCEL) return false;

			CS cs(m_cs);

			return CancelOrder(order.orderId);
		}
		std::optional<T> GetBestBid() const override
		{
			CS cs(m_cs);
			if (m_bid.empty()) return std::nullopt;
			return m_bid.begin()->second.front();
		}
		std::optional<T> GetBestAsk() const override
		{
			CS cs(m_cs);
			if (m_ask.empty()) return std::nullopt;
			return m_ask.begin()->second.front();
		}
	private:
		struct OrderLocation
		{
			uint32_t price = 0;
			typename std::list<T>::iterator it;
		};

		bool IsValidOrder(const T order)
		{
			return (order.symbolId == m_symbolId && order.price > 0 && order.quantity > 0);
		}

		bool IsInplaceModifiable(const T& oldOrder, const T& newOrder)
		{
			// Check if the price, side or type has changed
			if ((oldOrder.price != newOrder.price) ||
				(oldOrder.side != newOrder.side) ||
				(oldOrder.type != newOrder.type))
			{
				return false;
			}
			// Check quantity
			if (oldOrder.quantity < newOrder.quantity)
			{
				// Quantity increased, which is not allowed for in-place modification
				return false;
			}
			return true;
		}

		void AddOrder(const T order)
		{
			// Check if MARKET
			if (order.type == MARKET)
			{
				// MARKET orders are added to the front of the deque
				MarketOrder(order);
			}
			else
			{
				LimitOrder(order);
			}
		}

		uint32_t ProcessList(std::list<T>& list, uint32_t quantity)
		{
			while (!list.empty() && quantity > 0)
			{
				auto& bestOrder = list.front();

				if (quantity == bestOrder.quantity)
				{
					quantity = 0;	// finish
					// Remove both the market order and the best bid/ask order from the order book
					m_orders.erase(bestOrder.orderId);
					list.pop_front();
				}
				else if (quantity > bestOrder.quantity)
				{
					quantity -= bestOrder.quantity;
					// The market order's quantity is greater than the best bid/ask order's quantity
					// Remove the best bid/ask order's quantity
					m_orders.erase(bestOrder.orderId);
					list.pop_front();
				}
				else
				{
					// The market order's quantity is less than the best bid/ask order's quantity
					// Decrease the best bid/ask order's quantity
					list.front().quantity -= quantity;
					quantity = 0; // finish
				}
			}
			return quantity;
		}


		void MarketOrder(T order)
		{
			auto quantity = order.quantity;
			auto Matching = [&](auto& map)
				{
					if (map.empty())
					{
						return;
					}

					while (!map.empty() && quantity > 0)
					{
						auto it = map.begin();
						quantity = ProcessList(it->second, quantity);
						if (it->second.empty())
						{
							map.erase(it);
						}
					}
				};
			if (order.side == BUY)
			{
				Matching(m_ask);
			}
			else
			{
				Matching(m_bid);
			}
		}

		void LimitOrder(T order)
		{
			// Add the order to the appropriate map based on its side
			auto quantity = order.quantity;

			auto Matching = [&](auto& map, auto compare)
				{
					while (!map.empty() && quantity > 0)
					{
						auto it = map.begin();
						if (compare(it->first, order.price))
						{
							break;
						}

						// The price can be matched, so we need to process the orders in the list
						quantity = ProcessList(it->second, quantity);

						if (it->second.empty())
						{
							map.erase(it);
						}
						if (quantity == 0)
						{
							return; // finish
						}
					}
				};
			if (order.side == BUY)
			{
				Matching(m_ask, [](const uint32_t a, const uint32_t b) { return a > b; });
			}
			else
			{
				Matching(m_bid, [](const uint32_t a, const uint32_t b) { return a < b; });
			}


			// Quantity of the market order or all orders in m_ask have been eaten
			if (quantity != 0)
			{
				// Get the current timestamp (uint64_t) and update the order's timestamp with it
				auto timestamp = std::chrono::duration_cast<std::chrono::microseconds>(
					std::chrono::system_clock::now().time_since_epoch()).count();

				// Add the order to the bid/ask map if there are no bids/asks
				T newOrder = order;
				newOrder.timestamp = timestamp;
				newOrder.quantity = quantity;
				newOrder.action = ADD;

				auto Updating = [&](auto& map)
					{
						map[newOrder.price].push_back(newOrder);
						// Add the order to the orders map
						m_orders[newOrder.orderId] = { newOrder.price, std::prev(map[newOrder.price].end()) };
					};

				if (order.side == BUY)
				{
					Updating(m_bid);
				}
				else
				{
					Updating(m_ask);
				}

				return;	// finish
			}
		}

		bool CancelOrder(const uint64_t orderId)
		{
			// Find the target order in the map
			auto it = m_orders.find(orderId);
			if (it == m_orders.end())
			{
				return false;
			}

			OrderLocation& orderLocation = it->second;
			// Remove the order from the target map
			auto& orderInDeck = *(orderLocation.it);

			auto Erasing = [&](auto& map)
				{
					auto mapIt = map.find(orderLocation.price);
					if (mapIt != map.end())
					{
						mapIt->second.erase(orderLocation.it);
						if (mapIt->second.empty())
						{
							map.erase(mapIt);
						}
					}
					// Remove the order from the orders map
					m_orders.erase(it);
				};
			if (orderInDeck.side == BUY)
			{
				Erasing(m_bid);
			}
			else
			{
				Erasing(m_ask);
			}
			return true;
		}

		void ModifyOrder(T& oldOrder, const T newOrder)
		{
			oldOrder.quantity = newOrder.quantity;
		}

		uint32_t m_symbolId;
		mutable CriticalSection m_cs;
		std::unordered_map<uint64_t, OrderLocation> m_orders;
		std::map<uint32_t, std::list<T>, std::greater<uint32_t>> m_bid;
		std::map<uint32_t, std::list<T>, std::less<uint32_t>> m_ask;
	};
}
