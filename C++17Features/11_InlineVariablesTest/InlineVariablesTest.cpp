#include "pch.h"
#include "gtest/gtest.h"
#include "..\11_InlineVariables\InlineVariables_Basic.h"

// External function declared in the CPP file for testing ODR compliance

// Define the test fixture class
namespace InlineVariablesTest
{
	class InlineVariablesTest : public ::testing::Test
	{
	protected:
		INLINEVARIABLES_Basic::InlineVariables_Basic m_iv;
		void SetUp() override
		{
			INLINEVARIABLES_Basic::Counter::instanceCount = 0;
		}
		void TearDown() override {}
	};

	// Test Case 1: Global Inline Constant Access
	TEST_F(InlineVariablesTest, GlobalConstant_AccessCorrect)
	{
		// Check local access
		ASSERT_EQ("C++17 Feature Set v1.0", m_iv.getVersion());

		// Check direct access
		ASSERT_EQ("C++17 Feature Set v1.0", INLINEVARIABLES_Basic::VERSION_STRING);
	}

	// Test Case 2: Inline Map Access
	TEST_F(InlineVariablesTest, InlineMap_AccessCorrect)
	{
		// Check access via the class method
		ASSERT_EQ(30, m_iv.getDefaultTimeout());

		// Check direct access
		ASSERT_EQ(3, INLINEVARIABLES_Basic::CONFIG_DEFAULT.at("Retries"));

		// Check that the variable is accessible from another "translation unit" (simulated by get_inline_timeout())
		ASSERT_EQ(30, INLINEVARIABLES_Basic::get_inline_timeout());
	}

	// Test Case 3: Inline Static Member Variable (ODR check via linker)
	TEST_F(InlineVariablesTest, StaticCounter_IsSingleInstance)
	{
		// Start: 0

		// 1. Create instance in the test (Count: 1)
		INLINEVARIABLES_Basic::Counter c1;
		ASSERT_EQ(1, INLINEVARIABLES_Basic::Counter::instanceCount);

		// 2. Create instance in the external function (Count: 2)
		// access_inline_counter increments the count, then returns the new value, then c2 is destroyed
		int result_count = INLINEVARIABLES_Basic::access_inline_counter();
		// The count returned by the function is 2, but c2 is destroyed immediately after return
		ASSERT_EQ(1, INLINEVARIABLES_Basic::Counter::instanceCount);

		// 3. Create instance locally (Count: 2)
		INLINEVARIABLES_Basic::Counter c3;
		ASSERT_EQ(2, INLINEVARIABLES_Basic::Counter::instanceCount);

		// The count must be consistent, proving that the single 'instanceCount' is shared
		// across the test file and the Basic CPP file.
	}

}
