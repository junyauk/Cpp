#include "pch.h"
#include "gtest\gtest.h"
#include "..\10_NonTypeTemplate\NonTypeTemplate_Basic.h"

// Define the test fixture class
namespace NonTypeTemplateTest
{
	class AutoNTTPTest : public ::testing::Test
	{
	protected:
		NONTYPETEMPLATE_Basic::AutoNTTP_Basic m_nttp;
		void SetUp() override {}
		void TearDown() override {}
	};

	// Test Case 1: Int value deduction
	TEST_F(AutoNTTPTest, IntDeduction_CorrectValue)
	{
		std::string result = m_nttp.testIntDeducation();

		ASSERT_EQ("10", result);

		// Conceptual: Check the deduced type
		using IntNTTP = NONTYPETEMPLATE_Basic::CompileTimeValue<10>;
		static_assert(std::is_same_v<IntNTTP::ValueType, int>, "Type must be int");
	}

	// Test Case 2: Bool value deduction
	TEST_F(AutoNTTPTest, BoolDeduction_CorrectValue)
	{
		std::string result = m_nttp.testBoolDeducation();
		ASSERT_EQ("true", result);

		// Conceptual: Check the deduced type
		using BoolNTTP = NONTYPETEMPLATE_Basic::CompileTimeValue<true>;
		static_assert(std::is_same_v<BoolNTTP::ValueType, bool>, "Type must be bool");
	}

	// Test Case 3: Operation with different NTTP types
	TEST_F(AutoNTTPTest, MultiplierOperation_CorrectCalculation)
	{
		// Multiplier is 20L (long). Base value is 5L. Result: 100L
		long result = m_nttp.testMultiplierOperation(5L);
		ASSERT_EQ(100L, result);

		// Multiplier is 20L (long). Base value is 100L. Result: 2000L
		result = m_nttp.testMultiplierOperation(100L);
		ASSERT_EQ(2000L, result);

		// Conceptual: Check the deduced type and size
		using LongMultiplier = NONTYPETEMPLATE_Basic::ArrayMultiplier<5, 20L>;
		static_assert(LongMultiplier::getSize() == 5, "Size must be 5");
		static_assert(std::is_same_v<LongMultiplier::ResultType, long>, "Multiplier type must be long");
	}

}
