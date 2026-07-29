#include "pch.h"
#include "gtest/gtest.h"
#include "..\04_Variant\Variant_Advance.h"
#include <string>
#include <variant>
#include <stdexcept>

namespace VariantAdvanceTest
{
	class VariantAdvanceTest : public ::testing::Test
	{
	protected:
		VARIANT_Advance::Variant_Advance m_adv;
	};

	// Test Case 1a: Multiple Visit - Case (int, int)
	TEST_F(VariantAdvanceTest, MultipleVisit_IntInt)
	{
		// VariantA holds int(5), VariantB holds int(10)
		VARIANT_Advance::VariantA vA = 5;
		VARIANT_Advance::VariantB vB = 10;

		std::string result = m_adv.processMultipleVariants(vA, vB);
		// Expect 5 * 10 = 50
		ASSERT_EQ("Both Int: 50", result);
	}

	// Test Case 1b: Multiple Visit - Case (string, double)
	TEST_F(VariantAdvanceTest, MultipleVisit_StringDouble)
	{
		// VariantA holds string("Test"), VariantB holds double(3.5)
		VARIANT_Advance::VariantA vA = std::string("Test");
		VARIANT_Advance::VariantB vB = 3.5;

		std::string result = m_adv.processMultipleVariants(vA, vB);
		// Expect specific string output
		ASSERT_EQ("String (Test) and Double (3.5)", result);
	}

	// Test Case 2a: Type-safe Error Handling - Success
	TEST_F(VariantAdvanceTest, ErrorHandling_Success)
	{
		VARIANT_Advance::ResultType result = m_adv.calculateValue(10.0);

		// Verify success via safe access function
		ASSERT_EQ("SUCCESS: Value is 25.000000", m_adv.checkResultForError(result));

		// Verify success via std::get (should not throw)
		ASSERT_NO_THROW(ASSERT_EQ(25.0, std::get<VARIANT_Advance::SuccessType>(result)));
	}

	// Test Case 2b: Type-safe Error Handling - Error
	TEST_F(VariantAdvanceTest, ErrorHandling_Error)
	{
		VARIANT_Advance::ResultType result = m_adv.calculateValue(-5.0);

		// Verify error via safe access function
		ASSERT_EQ("ERROR: Code -1, Message: Input cannot be negative.", m_adv.checkResultForError(result));

		// Verify error via std::get (should throw)
		ASSERT_THROW(
			{
				std::get<VARIANT_Advance::SuccessType>(result);
			},
			std::bad_variant_access);
	}

	// Test Case 3a: std::monostate - Initial state
	TEST_F(VariantAdvanceTest, Monostate_Initial)
	{
		// Default initialized StatusVariant holds std::monostate
		VARIANT_Advance::StatusVariant status;

		ASSERT_EQ("Status: Uninitialized/Empty", m_adv.checkStatus(status));
	}

	// Test Case 3b: std::monostate - Active value
	TEST_F(VariantAdvanceTest, Monostate_ActiveValue)
	{
		// StatusVariant holds int(42)
		VARIANT_Advance::StatusVariant status = 42;

		ASSERT_EQ("Status: Int Value 42", m_adv.checkStatus(status));
	}
}
