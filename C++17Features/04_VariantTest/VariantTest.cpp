#include "pch.h"
#include <stdexcept>
#include <string>
#include "gtest/gtest.h"
#include "..\04_Variant\Variant_Basic.h"

// Define the test fixture class
namespace VariantTest
{
	class VariantTest : public testing::Test
	{
	protected:
		Variant_Basic::Variant_Basic m_vb;
		void SetUp() override
		{
			// Ensure m_vb is in a known state (constructor handles initial values)
			m_vb.clear();
			m_vb.addValue(10);
			m_vb.addValue(5.0);
			m_vb.addValue(std::string{ "Test" });
		}

		void TearDown() override
		{
			// Cleanup is implicit through the destructor, but clear is good practice for explicit cleanup
		}
	};

	// Test Case 3: Check Type (holds_alternative)
	TEST_F(VariantTest, GetTypeAtIndex_CorrectTypes)
	{
		// Index 0: int
		ASSERT_EQ("int", m_vb.getTypeAtIndex(0));
		// Index 1: double
		ASSERT_EQ("double", m_vb.getTypeAtIndex(1));
		// Index 2: std::string
		ASSERT_EQ("std::string", m_vb.getTypeAtIndex(2));
	}

	// Test Case 4: Access Value (std::get<T>) - Correct Access
	TEST_F(VariantTest, GetIntAt_CorrectlyGetsInt)
	{
		// Index 0 holds int 10
		ASSERT_EQ(10, m_vb.getIntAt(0));
	}

	// Test Case 4: Access Value (std::get<T>) - Incorrect Access Throws
	TEST_F(VariantTest, GetIntAt_ThrowsBadAccess)
	{
		// Index 1 holds a double (5.0). Trying to get an int should throw std::bad_variant_access.
		ASSERT_THROW(m_vb.getIntAt(1), std::bad_variant_access);
	}

	// Test Case 5: Processing using std::visit
	TEST_F(VariantTest, ProcessAllValues_AppliesVisitorCorrectly)
	{
		// Initial values: 10 (int), 5.0 (double), "Test" (string)

		// Process the values (doubles int/double, appends "!!!" to string)
		m_vb.processAllValues();

		// Check Int (Index 0): 10 -> 20
		ASSERT_TRUE(std::holds_alternative<int>(m_vb.m_dataList.at(0)));
		ASSERT_EQ(20, std::get<int>(m_vb.m_dataList.at(0)));

		// Check Double (Index 1): 5.0 -> 10.0
		ASSERT_TRUE(std::holds_alternative<double>(m_vb.m_dataList.at(1)));
		ASSERT_EQ(10.0, std::get<double>(m_vb.m_dataList.at(1)));

		// Check String (Index 2): "Test" -> "Test!!!"
		ASSERT_TRUE(std::holds_alternative<std::string>(m_vb.m_dataList.at(2)));
		ASSERT_EQ("Test!!!", std::get<std::string>(m_vb.m_dataList.at(2)));
	}

	// Test Case 6: Processing using std::visit to get a return value (convertValueToString)
	TEST_F(VariantTest, ConvertValueToString_Int)
	{
		// Index 0 holds int 10
		auto result = m_vb.convertValueToString(0);
		// std::to_string(10) is "10"
		ASSERT_EQ("10", result);
	}

	TEST_F(VariantTest, ConvertValueToString_Double)
	{
		// Index 1 holds double 5.0
		auto result = m_vb.convertValueToString(1);
		// std::to_string(5.0) will be "5.000000" (or similar, depending on precision, but "5" or "5.0" is generally sufficient)
		// We will check if it starts with "5" to avoid checking exact precision.
		ASSERT_TRUE(result.find("5.") == 0 || result == "5");
	}

	TEST_F(VariantTest, ConvertValueToString_String)
	{
		// Index 2 holds string "Test"
		auto result = m_vb.convertValueToString(2);
		ASSERT_EQ("Test", result);
	}

	TEST_F(VariantTest, ConvertValueToString_IndexOutOfBounds)
	{
		// Index 3 is out of bounds
		ASSERT_THROW(m_vb.convertValueToString(3), std::out_of_range);
	}
}

