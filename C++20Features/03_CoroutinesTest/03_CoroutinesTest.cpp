#include "pch.h"
#include "..\03_Coroutines\Coroutines_Basic.h"

using namespace Coroutines_Basic;

namespace Coroutines_Basic_Test
{
	class CoroutinesBasicTest : public ::testing::Test
	{
	protected:
		CoroutinesBasic m_coroutineBasic;
	};

	// Test case for the sequence generator using co_yield
	TEST_F(CoroutinesBasicTest, SequenceGenerator_Basic)
	{
		// Create the generator. Execution is suspended immediately (initial_suspend).
		auto generator = m_coroutineBasic.createSequenceGenerator(10, 3);

		// 1st next(): Starts execution -> co_yield 10 -> suspends
		auto val1 = generator.next();
		ASSERT_TRUE(val1.has_value());
		EXPECT_EQ(10, val1.value());

		// 2nd next(): Resumes execution -> co_yield 11 -> suspends
		auto val2 = generator.next();
		ASSERT_TRUE(val2.has_value());
		EXPECT_EQ(11, val2.value());

		// 3rd next(): Resumes execution -> co_yield 12 -> suspends
		auto val3 = generator.next();
		ASSERT_TRUE(val3.has_value());
		EXPECT_EQ(12, val3.value());

		// 4th next(): Resumes execution -> reaches co_return -> finishes
		auto val4 = generator.next();
		ASSERT_FALSE(val4.has_value());
	}

	// Test case for an empty sequence
	TEST_F(CoroutinesBasicTest, SequenceGenerator_Empty)
	{
		auto generator = m_coroutineBasic.createSequenceGenerator(10, 0);
		auto val = generator.next();

		// Should finish immediately on the first next()
		EXPECT_FALSE(val.has_value());
	}

	// Test case to collect all results into a single string
	TEST_F(CoroutinesBasicTest, SequenceGenerator_CollectAll)
	{
		auto generator = m_coroutineBasic.createSequenceGenerator(1, 5);
		std::stringstream ss;

		// Loop until the coroutine finishes (next() returns std::nullopt)
		while (auto val = generator.next())
		{
			ss << val.value() << " ";
		}
		EXPECT_EQ("1 2 3 4 5 ", ss.str());
	}

	// ------------------------------------------------------------------------
	class CoroutinesGeneratorTest : public ::testing::Test
	{
	protected:
		CoroutinesGenerator m_fibonacci;
	};

	// Test case for the Fibonacci sequence generator
	TEST_F(CoroutinesGeneratorTest, FibonacciGenerator_Basic)
	{
		// Generates: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34 (limit=50)
		auto generator = m_fibonacci.createFibonacciGenerator(50);
		std::vector<int> expected = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34 };
		std::vector<int> result;

		while (auto val = generator.next())
		{
			result.push_back(val.value());
		}

		// Assert that the generated sequence matches the expected sequence
		ASSERT_EQ(expected.size(), result.size());
		EXPECT_EQ(expected, result);
	}

	// Test case for a small limit
	TEST_F(CoroutinesGeneratorTest, FibonacciGenerator_SmallLimit)
	{
		// Generates: 0, 1, 1, 2, 3 (limit=4)
		auto generator = m_fibonacci.createFibonacciGenerator(4);
		std::vector<int> expected = { 0, 1, 1, 2, 3 };
		std::vector<int> result;

		while (auto val = generator.next())
		{
			result.push_back(val.value());
		}
		EXPECT_EQ(expected, result);
	}

	// Test case for limit less than 1
	TEST_F(CoroutinesGeneratorTest, FibonacciGenerator_NoOutput)
	{
		auto generator = m_fibonacci.createFibonacciGenerator(0);

		// The generator should immediately co_return, yielding no value.
		EXPECT_FALSE(generator.next().has_value());
	}

	// ------------------------------------------------------------------------

	// Test case for the infinite sequence generator, halted externally
	TEST_F(CoroutinesGeneratorTest, InfiniteGenerator_ExternalStop)
	{
		int start_value = 100;
		int limit = 5;

		// Generates: 100, 101, 102, 103, 104
		auto generator = m_fibonacci.createInfiniteNumberGenerator(start_value);
		std::vector<int> results;

		for (int i = 0; i < limit; ++i)
		{
			auto val = generator.next();
			ASSERT_TRUE(val.has_value());
			results.push_back(val.value());
		}

		std::vector<int> expected = { 100, 101, 102, 103, 104 };
		EXPECT_EQ(expected, results);

		// Verification that the coroutine is still suspended and ready to continue
		auto next_val = generator.next();
		ASSERT_TRUE(next_val.has_value());
		EXPECT_EQ(105, next_val.value());
	}


}
