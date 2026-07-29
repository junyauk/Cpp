#include "pch.h"
#include "..\02_Ranges\Ranges_Basic.h"

using namespace Range_Basic;

namespace Ranges_Basic_Test
{
	class RangesBasicTest : public ::testing::Test
	{
	protected:
		RangeBasic m_rangeBasic;
		std::vector<int> m_inputData = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		std::vector<int> m_targetData = { 5, 1, 5, 2, 5, 3 };
	};

	// Test case for the data processing pipeline (filter and transform)
	TEST_F(RangesBasicTest, ProcessPipeline_FilterTransform)
	{
		// Even numbers in m_inputData: 2, 4, 6, 8, 10
		// Transformed (x * 2): 4, 8, 12, 16, 20
		std::string expected = "4 8 12 16 20";
		std::string result = m_rangeBasic.processPipeline(m_inputData);

		EXPECT_EQ(expected, result);
	}

	// Test case for std::ranges::count
	TEST_F(RangesBasicTest, RangesAlgorithm_Count)
	{
		// Count of 5 in m_targetData: 3
		int expected = 3;
		int result = m_rangeBasic.countTarget(m_targetData);
		EXPECT_EQ(expected, result);
	}

	// Test case for std::views::take and combining with an existing algorithm
	TEST_F(RangesBasicTest, RangesView_TakeAndSum)
	{
		// Sum of the first 4 elements of m_inputData: 1 + 2 + 3 + 4 = 10
		int expected = 10;
		int result = m_rangeBasic.sumFirstN(m_inputData, 4);
		EXPECT_EQ(expected, result);
	}
	// Test case to show that views work lazily (optional, for conceptual understanding)
	TEST_F(RangesBasicTest, View_IsEmpty)
	{
		std::vector<int> empty_vec;
		std::string result = m_rangeBasic.processPipeline(empty_vec);
		EXPECT_TRUE(result.empty());
	}
}

