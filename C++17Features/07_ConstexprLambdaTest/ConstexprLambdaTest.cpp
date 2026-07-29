#include "pch.h"
#include <algorithm>
#include <array>
#include "..\07_ConstexprLambda\ConstexprLambda_Basic.h"

namespace ConstexprLambdaTest
{
	class ConstexprLambdaTest : public ::testing::Test
	{
	protected:
		CONSTEXPRLAMBDA_Basic::ConstexprLambda_Basic m_cl;

		void SetUp() override
		{
			m_cl.clear();
		}

		void TearDown() override
		{
			// Nothing specific needed
		}
	};

	// Test Case 1: Basic Constexpr Lambda used at runtime
	TEST_F(ConstexprLambdaTest, CalculateSquare_Runtime)
	{
		// Test standard runtime usage
		ASSERT_EQ(25, m_cl.calculateSquare(5));
		ASSERT_EQ(100, m_cl.calculateSquare(10));
	}

	// Test Case 2: Compile-Time Array Initialization
	TEST_F(ConstexprLambdaTest, GetCompileTimeArray_CorrectValues)
	{
		// Retrieve the array initialized at compile time
		std::array<int, CONSTEXPRLAMBDA_Basic::ConstexprLambda_Basic::ARRAY_SIZE> result_array = m_cl.getCompileTimeArray();

		// Check size
		ASSERT_EQ(5, result_array.size());

		// Check contents (10, 20, 30, 40, 50)
		ASSERT_EQ(10, result_array[0]);
		ASSERT_EQ(30, result_array[2]);
		ASSERT_EQ(50, result_array[4]);

		// --- Further Check: Proving it *can* be used at compile time ---
		// (This is conceptual; actual compiler proof requires compiler specific output)
		// We can test if the result can be used to initialize a constexpr variable:
		constexpr auto constexpr_array = CONSTEXPRLAMBDA_Basic::ConstexprLambda_Basic::getCompileTimeArray();
		ASSERT_EQ(10, constexpr_array[0]);
	}

	// Test Case 3: Runtime Summation using the constexpr lambda
	TEST_F(ConstexprLambdaTest, CalculateRuntimeSum_CorrectResult)
	{
		// Sum of squares from 1 to 3: 1^2 + 2^2 + 3^2 = 1 + 4 + 9 = 14
		ASSERT_EQ(14, m_cl.calculateRuntimeSum(3));

		// Sum of squares from 1 to 5: 1+4+9+16+25 = 55
		ASSERT_EQ(55, m_cl.calculateRuntimeSum(5));
	}
}


