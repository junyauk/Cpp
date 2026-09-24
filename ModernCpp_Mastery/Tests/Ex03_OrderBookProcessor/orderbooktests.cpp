#include "gtest/gtest.h"
#include "classicorderbook.h"
#include "modernorderbook.h"
#include <random>
#include <thread>

using namespace Ex03_OrderBookProcessor;

namespace Ex03_OrderBookProcessorTests
{

	template<typename T>
	class OrderBookTests : public ::testing::Test {};
	using OrderBookTestsImplementations = ::testing::Types<ClassicOrderBook<Order>, ModernOrderBook<Order>>;
	TYPED_TEST_CASE(OrderBookTests, OrderBookTestsImplementations);

	TYPED_TEST(OrderBookTests, BasicAddMatching)
	{
		std::vector<Order> orders =
		{
			{1, 1, 1, 100, 1000, BUY, LIMIT, ADD},
			{2, 1, 1, 100, 1010, SELL, LIMIT, ADD}
		};

		TypeParam book(1);
		std::optional<Order> ret;

		// Buy
		book.Add(orders[0]);
		ret = book.GetBestBid();
		EXPECT_EQ(1, ret.value().orderId);
		EXPECT_NE(1, ret.value().timestamp);
		EXPECT_EQ(1, ret.value().symbolId);
		EXPECT_EQ(100, ret.value().price);
		EXPECT_EQ(1000, ret.value().quantity);
		EXPECT_EQ(BUY, ret.value().side);
		EXPECT_EQ(LIMIT, ret.value().type);
		EXPECT_EQ(ADD, ret.value().action);
		book.Add(orders[1]);

		// Sell
		ret = book.GetBestBid();
		EXPECT_TRUE(ret == std::nullopt);
		ret = book.GetBestAsk();
		EXPECT_TRUE(ret != std::nullopt);
		EXPECT_EQ(2, ret.value().orderId);
		EXPECT_NE(1, ret.value().timestamp);
		EXPECT_EQ(1, ret.value().symbolId);
		EXPECT_EQ(100, ret.value().price);
		EXPECT_EQ(10, ret.value().quantity);	// left 10 (1010 - 1000)
		EXPECT_EQ(SELL, ret.value().side);
		EXPECT_EQ(LIMIT, ret.value().type);
		EXPECT_EQ(ADD, ret.value().action);
	}

	TYPED_TEST(OrderBookTests, RejectInvalidOrders)
	{
		std::vector<Order> orders =
		{
			{ 1, 1, 2, 100, 1000, BUY,  LIMIT, ADD},		// Wrong SymbolId
			{ 2, 1, 3, 100, 1010, SELL, LIMIT, ADD},		// Wrong SymbolId
			{ 3, 1, 1,   0, 1010, BUY,  LIMIT, ADD },		// Price is zero
			{ 4, 1, 1, 100,    0, SELL, LIMIT, ADD },		// Quantity is zero

			{ 5, 1, 1, 100, 1000, BUY,  LIMIT, ADD },		// Sample
			{ 6, 1, 1, 200, 1000, SELL, LIMIT, ADD },		// Sample
			{ 5, 1, 1, 100, 1000, BUY,  LIMIT, MODIFY },	// Calling with wrong action
			{ 5, 1, 1, 100, 1000, BUY,  LIMIT, CANCEL },	// Calling with wrong action
			{ 6, 1, 1, 100, 1000, SELL, LIMIT, MODIFY },	// Calling with wrong action
			{ 6, 1, 1, 100, 1000, SELL, LIMIT, CANCEL }		// Calling with wrong action
		};

		TypeParam book(1);

		// Wrong SymbolId -> invalid
		book.Add(orders[0]);
		EXPECT_EQ(std::nullopt, book.GetBestBid());
		EXPECT_EQ(std::nullopt, book.GetBestAsk());
		book.Add(orders[1]);
		EXPECT_EQ(std::nullopt, book.GetBestBid());
		EXPECT_EQ(std::nullopt, book.GetBestAsk());
		book.Add(orders[2]);
		EXPECT_EQ(std::nullopt, book.GetBestBid());
		EXPECT_EQ(std::nullopt, book.GetBestAsk());
		book.Add(orders[3]);
		EXPECT_EQ(std::nullopt, book.GetBestBid());
		EXPECT_EQ(std::nullopt, book.GetBestAsk());

		// Calling Add with Orders (MODIFY or CANCEL) -> invalid
		book.Add(orders[6]);
		book.Add(orders[7]);
		EXPECT_EQ(std::nullopt, book.GetBestBid());
		EXPECT_EQ(std::nullopt, book.GetBestAsk());
		book.Add(orders[8]);
		book.Add(orders[9]);
		EXPECT_EQ(std::nullopt, book.GetBestBid());
		EXPECT_EQ(std::nullopt, book.GetBestAsk());

		// Calling Modify and Cancel with an Order(ADD) -> invalid
		EXPECT_FALSE(book.Modify(orders[4]));
		EXPECT_FALSE(book.Modify(orders[5]));
		EXPECT_FALSE(book.Modify(orders[7]));
		EXPECT_FALSE(book.Modify(orders[9]));
		EXPECT_FALSE(book.Cancel(orders[4]));
		EXPECT_FALSE(book.Cancel(orders[5]));
		EXPECT_FALSE(book.Cancel(orders[6]));
		EXPECT_FALSE(book.Cancel(orders[8]));

		// Add Orders as preparation for Modify and Cancel
		book.Add(orders[4]);	// Buy
		book.Add(orders[5]);	// Sell
		EXPECT_NE(std::nullopt, book.GetBestBid());
		EXPECT_NE(std::nullopt, book.GetBestAsk());
		// Modify with Orders (CANCEL) -> invalid
		EXPECT_FALSE(book.Modify(orders[7]));
		EXPECT_FALSE(book.Modify(orders[9]));
		// Cancel with Orders (MODIFY) -> invalid
		EXPECT_FALSE(book.Cancel(orders[6]));
		EXPECT_FALSE(book.Cancel(orders[8]));
	}

	TYPED_TEST(OrderBookTests, BasicModifyOrders)
	{
		std::vector<Order> orders =
		{
			{ 1, 1, 1, 100, 1000,  BUY, LIMIT,  ADD },
			{ 1, 1, 1,  10, 1000,  BUY, LIMIT,  MODIFY },	// Not inplace modifiable
			{ 1, 1, 1,  10,   10,  BUY, LIMIT,  MODIFY },	// Inplace modifiable
			{ 1, 1, 1,  10,   10, SELL, LIMIT,  MODIFY },	// Not inplace modifiable
			{ 1, 1, 1,  10,   10, SELL, MARKET, MODIFY },	// Not inplace modifiable
		};

		TypeParam book(1);
		book.Add(orders[0]);
		EXPECT_NE(std::nullopt, book.GetBestBid());
		EXPECT_EQ(std::nullopt, book.GetBestAsk());

		// Not inplace modifiable (Cancel & Add)
		book.Modify(orders[1]);
		std::optional<Order> opt = book.GetBestBid();
		EXPECT_TRUE(opt.has_value());
		Order o = opt.value();
		EXPECT_EQ(10, o.price);
		EXPECT_EQ(1000, o.quantity);
		EXPECT_EQ(BUY, o.side);
		EXPECT_EQ(LIMIT, o.type);
		EXPECT_EQ(ADD, o.action);

		// Inplace modifiable
		book.Modify(orders[2]);
		opt = book.GetBestBid();
		EXPECT_TRUE(opt.has_value());
		o = opt.value();
		EXPECT_EQ(10, o.price);
		EXPECT_EQ(10, o.quantity);
		EXPECT_EQ(BUY, o.side);
		EXPECT_EQ(LIMIT, o.type);
		EXPECT_EQ(ADD, o.action);

		// Not inplace modifiable (Cancel & Add)
		book.Modify(orders[3]);
		opt = book.GetBestBid();
		EXPECT_FALSE(opt.has_value());
		opt = book.GetBestAsk();
		EXPECT_TRUE(opt.has_value());
		o = opt.value();
		EXPECT_EQ(10, o.price);
		EXPECT_EQ(10, o.quantity);
		EXPECT_EQ(SELL, o.side);
		EXPECT_EQ(LIMIT, o.type);
		EXPECT_EQ(ADD, o.action);

		// Not inplace modifiable (Cancel & Add(MARKET)) -> immediately consumed
		book.Modify(orders[4]);
		opt = book.GetBestAsk();
		EXPECT_FALSE(opt.has_value());
	}

	TYPED_TEST(OrderBookTests, BasicCancelOrders)
	{
		std::vector<Order> orders =
		{
			{ 1, 1, 1, 100, 1000,  BUY, LIMIT, ADD },
			{ 1, 1, 2, 100, 1010, SELL, LIMIT, CANCEL },	// Rejected because of wrong SymbolId
			{ 2, 1, 1, 100, 1010, SELL, LIMIT, CANCEL },	// Rejected because of wrong OrderId
			{ 1, 1, 1, 100, 1010, SELL, LIMIT, CANCEL },	// Cancelled
		};

		TypeParam book(1);
		book.Add(orders[0]);
		EXPECT_NE(std::nullopt, book.GetBestBid());
		EXPECT_EQ(std::nullopt, book.GetBestAsk());
		EXPECT_FALSE(book.Cancel(orders[1]));
		EXPECT_NE(std::nullopt, book.GetBestBid());
		EXPECT_FALSE(book.Cancel(orders[2]));
		EXPECT_NE(std::nullopt, book.GetBestBid());
		EXPECT_TRUE(book.Cancel(orders[3]));
		EXPECT_EQ(std::nullopt, book.GetBestBid());
	}

	Order GenerateOrder(uint32_t maxSymbolId)
	{
		thread_local static std::mt19937 engine(std::random_device{}()); // Use thread_local static for performance
		std::uniform_int_distribution<uint32_t> dist(0, 2);
		std::uniform_int_distribution<uint32_t> dist6(0, maxSymbolId - 1);
		std::uniform_int_distribution<uint32_t> dist10(0, 10000);

		std::vector<uint32_t> prices = {100, 150, 200, 250, 300, 350};
		std::vector<uint32_t> quantities = { 1000, 1500, 2000, 2500, 3000, 3500 };
		std::vector<Action> actions = { ADD, MODIFY, CANCEL };


		return {
			dist10(engine),	// orderId
			1,				// timestamp
			dist6(engine),	// symbolId
			prices[dist6(engine)],	// price
			quantities[dist6(engine)],	// quantity
			(dist6(engine) / 2) ? BUY : SELL,	// side
			(dist6(engine) / 2) ? LIMIT : MARKET, // type
			actions[dist(engine)] };	// action
	}


	TYPED_TEST(OrderBookTests, MultiThreadingConcurrencyTests)
	{
		std::vector<std::unique_ptr<TypeParam>> books;
		std::vector<std::jthread> threads;
		const static uint32_t NUM_SYMBOLS = 6;
		const static uint32_t NUM_ORDERS = 10000;
		// Preparing the books first
		for (uint32_t i = 0; i < NUM_SYMBOLS; ++i)
		{
			books.push_back(std::make_unique<TypeParam>(i));
		}
		for (uint32_t i = 0; i < NUM_SYMBOLS; ++i)
		{
			uint32_t index = i;
			threads.emplace_back([index, &books](std::stop_token st)
				{
					for (uint32_t j = 0; j < NUM_ORDERS; ++j)
					{
						auto order = GenerateOrder(NUM_SYMBOLS);
						order.symbolId = index;
						switch (order.action)
						{
						case ADD: books[order.symbolId]->Add(order); break;
						case MODIFY: books[order.symbolId]->Modify(order); break;
						case CANCEL: books[order.symbolId]->Cancel(order); break;
						}
					}
				});
		}
		for (auto& t : threads)
		{
			if (t.joinable())
			{
				t.join();
			}
		}

		for (uint32_t i = 0; i < NUM_SYMBOLS; ++i)
		{
			std::optional<Order> bid = books[i]->GetBestBid();
			std::optional<Order> ask = books[i]->GetBestAsk();
			if (bid.has_value())
			{
				EXPECT_EQ(i, bid.value().symbolId);
				EXPECT_TRUE(bid.value().price > 0);
				EXPECT_TRUE(bid.value().quantity > 0);
				EXPECT_EQ(BUY, bid.value().side);
			}

			if (ask.has_value())
			{
				EXPECT_EQ(i, ask.value().symbolId);
				EXPECT_TRUE(ask.value().price > 0);
				EXPECT_TRUE(ask.value().quantity > 0);
				EXPECT_EQ(SELL, ask.value().side);
			}

			if (bid.has_value() && ask.has_value())
			{
				EXPECT_LT(bid.value().price, ask.value().price);
			}
		}

		SUCCEED();
	}

}
