#include "pch.h"
#include <stdexcept>
#include <string>
#include "..\05_Any\Any_Basic.h"

// Define the test fixture class
namespace AnyTest
{
	class AnyTest : public ::testing::Test
	{
	protected:
		ANY_Basic::Any_Basic m_ab;

		void SetUp() override
		{
			m_ab.clear();
			// Re-set initial values for predictable testing
			m_ab.setConfigValue("AlphaInt", 100);
			m_ab.setConfigValue("BetaString", std::string{ "ValueB" });
		}
		void TearDown() override
		{
			// Nothing specific needed
		}
	};

	// Test Case 1 & 2: Safe Access (getConfigValueSafe) - Type Match
	TEST_F(AnyTest, GetConfigValueSafe_Int_TypeMatch)
	{
		auto result = m_ab.getConfigValueSafe<int>("AlphaInt");
		ASSERT_TRUE(result.has_value());
		ASSERT_EQ(100, result.value());
	}

	// Test Case 1 & 2: Safe Access (getConfigValueSafe) - Type Mismatch
	TEST_F(AnyTest, GetConfigValueSafe_Int_TypeMismatch)
	{
		// Key "BetaString" holds a std::string, attempting to retrieve as int
		auto result = m_ab.getConfigValueSafe<int>("BetaString");
		ASSERT_FALSE(result.has_value());	// Should return nullopt (disengaged optional)
	}

	// Test Case 1 & 2: Safe Access (getConfigValueSafe) - Key Not Found
	TEST_F(AnyTest, GetConfigValueSafe_KeyNotFound)
	{
		auto result = m_ab.getConfigValueSafe<std::string>("NotExistenKey");
		ASSERT_FALSE(result.has_value());
	}

	// Test Case 3: Unsafe Access (getStringConfigValueUnsafe) - Success
	TEST_F(AnyTest, GetStringConfigValueUnsafe_Success)
	{
		auto result = m_ab.getStringConfigValueUnsafe("BetaString");
		ASSERT_EQ("ValueB", result);
	}

	// Test Case 3: Unsafe Access (getStringConfigValueUnsafe) - Type Mismatch Throws
	TEST_F(AnyTest, GetStringConfigValueUnsafe_TypeMismatch_Throws)
	{
		// Key "AlphaInt" holds an int, attempting to retrieve as std::string
		ASSERT_THROW(m_ab.getStringConfigValueUnsafe("AlphaInt"), std::bad_any_cast);
	}

	// Test Case 4: Check Type (getConfigType)
	TEST_F(AnyTest, GetConfigType_ReturnsCorrectType)
	{
		ASSERT_EQ("int", m_ab.getConfigType("AlphaInt"));
		ASSERT_EQ("std::string", m_ab.getConfigType("BetaString"));
	}

	// Test Case 4: Check Type (getConfigType) - Key Not Found
	TEST_F(AnyTest, GetConfigType_KeyNotFound)
	{
		ASSERT_EQ("empty", m_ab.getConfigType("MissingKey"));
	}
}

