#include "pch.h"
#include "gtest/gtest.h"
#include "..\08_FoldExpressions\FoldExpressions_Basic.h"

namespace FoldExpressionsTest
{
	class FoldExpressionsTest : public ::testing::Test
	{
	protected:
		FOLDEXPRESSIONS_Basic::FoldExpressions_Basic m_fe;
		void SetUp() override { }
		void TearDown() override {}
	};

	// Test Case 1: Unary Left Fold - Summation
	TEST_F(FoldExpressionsTest, SumAll_Integers)
	{
		// 1 + 5 + 10 + 20 = 36
		ASSERT_EQ(36, m_fe.sumAll(1, 5, 10, 20));
	}

	TEST_F(FoldExpressionsTest, SumAll_MixedTypes)
	{
		// 10 + 5.5 + 4 = 19.5 (result type is double)
		ASSERT_DOUBLE_EQ(19.5, m_fe.sumAll(10, 5.5, 4));
	}

	// The case for an empty pack 'sumAll()' is ill-formed for '+' operator.
	// If you need to support it, you must use a binary fold: (0 + ... + args)

	// Test Case 2: Binary Right Fold - Stream Concatenation
	TEST_F(FoldExpressionsTest, Concatenate_MixedTypes)
	{
		// Start with 1.0, concatenate: "one", 2, "three"
		std::string result = m_fe.concatnate(1.0, "one", 2, "three");
		// Expected: "1.000000 : one : 2 : three" (Precision is implementation dependent)

		// Check for the core structure and values
		ASSERT_NE(std::string::npos, result.find("1"));
		ASSERT_NE(std::string::npos, result.find(" : one"));
		ASSERT_NE(std::string::npos, result.find(" : 2"));
		ASSERT_NE(std::string::npos, result.find(" : three"));
	}

	// Test Case 3: Unary Right Fold - Logical AND Check
	TEST_F(FoldExpressionsTest, AllTrue_AllTrue)
	{
		ASSERT_TRUE(m_fe.allTrue(true, true, 1 == 1, true));
	}

	TEST_F(FoldExpressionsTest, AllTrue_OneFalse)
	{
		ASSERT_FALSE(m_fe.allTrue(true, false, true));
	}

	TEST_F(FoldExpressionsTest, AllTrue_EmptyPack)
	{
		// Unary fold for '&&' evaluates to true for an empty pack.
		ASSERT_TRUE(m_fe.allTrue());
	}
}
