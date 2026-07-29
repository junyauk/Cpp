#include "pch.h"
#include "gtest/gtest.h"
#include <sstream>
#include "..\08_FoldExpressions\FoldExpressions_Advance.h"

namespace FoldExpressionsAdvanceTest
{
	class FoldExpressionsAdvanceTest : public ::testing::Test
	{
	protected:
	};

	// Test Case 1a: Logical Operations - All True (AND)
	TEST_F(FoldExpressionsAdvanceTest, LogicalFold_AllTrue)
	{
		// All true -> True
		ASSERT_TRUE(FOLDEXPRESSIONS_Advance::FoldExpressions_Advance::all_true(true, true, true));

		// One false -> False
		ASSERT_FALSE(FOLDEXPRESSIONS_Advance::FoldExpressions_Advance::all_true(true, false, true));

		// Empty fold (requires initial value 'true') -> True
		ASSERT_TRUE(FOLDEXPRESSIONS_Advance::FoldExpressions_Advance::all_true());
	}

	// Test Case 1b: Logical Operations - Any True (OR)
	TEST_F(FoldExpressionsAdvanceTest, LogicalFold_AnyTrue)
	{
		// One true -> True
		ASSERT_TRUE(FOLDEXPRESSIONS_Advance::FoldExpressions_Advance::any_true(false, true, false));

		// All false -> False
		ASSERT_FALSE(FOLDEXPRESSIONS_Advance::FoldExpressions_Advance::any_true(false, false, false));

		// Empty fold (requires initial value 'false') -> False
		ASSERT_FALSE(FOLDEXPRESSIONS_Advance::FoldExpressions_Advance::any_true());
	}

	// Test Case 2: Right vs. Left Fold (Comma Operator Side Effects)
	TEST_F(FoldExpressionsAdvanceTest, CommaFold_SequenceOfOperations)
	{
		int a = 0, b = 0, c = 0;

		// Uses FoldExpressions_Advance::Counter::sequence_increment (Unary Left Fold)
		// The expectation is that all variables are incremented sequentially.
		FOLDEXPRESSIONS_Advance::Counter::sequence_increment(a, b, c);

		// Check side effects
		ASSERT_EQ(1, a);
		ASSERT_EQ(1, b);
		ASSERT_EQ(1, c);
	}

	// Test Case 3: Stream Output
	TEST_F(FoldExpressionsAdvanceTest, StreamOutput_BinaryLeftFold)
	{
		std::stringstream ss;

		FOLDEXPRESSIONS_Advance::FoldExpressions_Advance::print_to_stream(
			ss, "Hello", ", ", 42, "!", 3.14
		);

		// Check the final output string
		// The output should be concatenated without extra spaces.
		ASSERT_EQ("Hello, 42!3.14\n", ss.str());
	}

}