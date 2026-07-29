#include "pch.h"
#include "gtest/gtest.h"
#include "..\02_IfSwitchInit\IfSwitchInit_Basic.h"

namespace IfSwitchInitTest
{
	class IfSwitchInitTest : public ::testing::Test
	{
	protected:
		IFSWITCHINIT_Basic::IfSwitchInit_Basic m_isi;
		void SetUp() override
		{
			// Initialize setup before each test
			m_isi.clear();
			m_isi = IFSWITCHINIT_Basic::IfSwitchInit_Basic();
		}
		void TearDown() override
		{
			// Clean up after each test
			m_isi.clear();
		}
	};

	// Test Case 1: if-initializer with map::find - Key Found
	TEST_F(IfSwitchInitTest, GetValueIfKeyExists_Found)
	{
		// Key '5' is expected to be found
		auto result = m_isi.getValueIfKeyExists(5);
		ASSERT_TRUE(result.has_value());
		ASSERT_EQ("Five", result.value());
	}


	// Test Case 1: if-initializer with map::find - Key Not Found
	TEST_F(IfSwitchInitTest, GetValueIfKeyExists_NotFound)
	{
		// Key '99' is not expected to be found
		auto result = m_isi.getValueIfKeyExists(99);
		ASSERT_FALSE(result.has_value());
	}

	// Test Case 2: if-initializer with RAII object - Condition True
	TEST_F(IfSwitchInitTest, CalculateMetricIfValid_Valid)
	{
		// Raw Value 10 -> Metric Value 20. Threshold 15. Condition (20 >= 15) is true.
		auto result = m_isi.calculateMetricIfValid(10, 15);
		ASSERT_TRUE(result.has_value());
		ASSERT_EQ(20, result.value());
	}

	// Test Case 2: if-initializer with RAII object - Condition False
	TEST_F(IfSwitchInitTest, CalculateMetricIfValid_Invalid)
	{
		// Raw Value 5 -> Metric Value 10. Threshold 15. Condition (10 >= 15) is false.
		auto result = m_isi.calculateMetricIfValid(5, 15);
		ASSERT_FALSE(result.has_value());
	}

	// Test Case 3: switch-initializer - Case Match
	TEST_F(IfSwitchInitTest, ProcessStatusCode_CaseMatch)
	{
		// initialValue=1 -> statusCode=10
		ASSERT_EQ("Warning: High Value", m_isi.processStatusCode(1));
		// initialValue=0 -> statusCode=0
		ASSERT_EQ("Status: OK", m_isi.processStatusCode(0));
	}

	// Test Case 3: switch-initializer - Default Case
	TEST_F(IfSwitchInitTest, ProcessStatusCode_DefaultCase)
	{
		// initialValue=100 -> statusCode=20
		ASSERT_EQ("Unknown Status: 20", m_isi.processStatusCode(100));
		// initialValue=-5 -> statusCode=-1
		ASSERT_EQ("Error: Negative Input", m_isi.processStatusCode(-5));
	}
}
