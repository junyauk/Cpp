#include "pch.h"
#include "gtest/gtest.h"
#include "..\05_Any\Any_Advance.h"
#include <string>
#include <any>
#include <stdexcept>
#include <typeinfo>

namespace AnyAdvanceTest
{
	class AnyAdvanceTest : public ::testing::Test
	{
	protected:
		ANY_Advance::Any_Advance m_adv;

		void SetUp() override
		{
			// Setup configuration map with various types
			m_adv.setConfig("Port", 8080);		// int
			m_adv.setConfig("Timeout", 2.5);	// double
			m_adv.setConfig("Host", std::string("localhost")); // string
			m_adv.setConfig("Debug", true);		// bool
		}
	};

	// Test Case 1a: Dynamic Configuration - int retrieval
	TEST_F(AnyAdvanceTest, ConfigRetrieval_Int)
	{
		ASSERT_EQ("Type: int, Value: 8080", m_adv.getConfigInfo("Port"));
	}

	// Test Case 1b: Dynamic Configuration - double retrieval
	TEST_F(AnyAdvanceTest, ConfigRetrieval_Double)
	{
		// Note: Floating point output might need trimming, but should be close.
		ASSERT_EQ("Type: double, Value: 2.500000", m_adv.getConfigInfo("Timeout"));
	}

	// Test Case 1c: Dynamic Configuration - string retrieval
	TEST_F(AnyAdvanceTest, ConfigRetrieval_String)
	{
		ASSERT_EQ("Type: std::string, Value: localhost", m_adv.getConfigInfo("Host"));
	}

	// Test Case 2a: Type Safety - Missing key
	TEST_F(AnyAdvanceTest, TypeSafety_MissingKey)
	{
		ASSERT_EQ("Key not found.", m_adv.getConfigInfo("NotExistent"));
	}

	// Test Case 2b: Type Safety - Incorrect type (bool stored, expecting int)
	TEST_F(AnyAdvanceTest, TypeSafety_IncorrectCast)
	{
		// 'Debug' is stored as a bool, but getConfigInfo does not handle bool, 
		// leading to the default "Unknown Type" branch.
		ASSERT_NE(std::string::npos, m_adv.getConfigInfo("Debug").find("Type: Unknown"));

		// Test direct throwing behavior of std::any_cast (Outside of the function)
		std::any any_val = true;
		ASSERT_THROW
		(
			{
				std::any_cast<int>(any_val);
			},
			std::bad_any_cast
		);
	}

	// Test Case 3: Copy vs. Move Cost (Semantic Verification)
	TEST_F(AnyAdvanceTest, MoveCost_CheckMoveConstructor)
	{
		// 1. Create a large payload (Original)
		ANY_Advance::BigPayload payload("TestPayload", 100000);

		// 2. processPayloadCost: 
		//    a) Copy 'payload' into 'any_payload' (Invokes Copy Constructor -> _C)
		//    b) Move the content out of 'any_payload' (Invokes Move Constructor -> _M)
		std::string result = m_adv.processPayloadCost(payload);

		// The final label should reflect both operations: Original -> Copy -> Move
		ASSERT_EQ("TestPayload_C_M", result);

		// This confirms that std::any first copies the value, 
		// and then std::any_cast<T&&>(std::move(any)) correctly moves it out.
	}
}
