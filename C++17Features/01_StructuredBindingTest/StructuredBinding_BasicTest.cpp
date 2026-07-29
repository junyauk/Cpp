#include "pch.h"
#include "..\01_StructuredBinding\structured_binding_basic.h"

namespace StructuredBindingTest
{
	class StructuredBindingTest : public ::testing::Test
	{
	protected:
		STRUCTUREDBINDING_Basic::StructuredBinding_Basic m_sb;

		void SetUp() override
		{
			// Initialize setup before each test
			m_sb.clear();
			m_sb.m_dataMap.insert({ 10, "Ten" });
			m_sb.m_dataMap.insert({ 20, "Twenty" });
		}

		void TearDown() override
		{
			// Clean up after each test
			m_sb.clear();
		}
	};

	TEST_F(StructuredBindingTest, InsertToMap_NewKey_Success)
	{
		bool inserted = m_sb.insertToMap(30, "Thirty");
		ASSERT_TRUE(inserted);
		ASSERT_EQ(3, m_sb.m_dataMap.size());
		ASSERT_EQ("Thirty", m_sb.m_dataMap.at(30));
	}

	TEST_F(StructuredBindingTest, InsertToMap_ExistingKey_Failure)
	{
		bool inserted = m_sb.insertToMap(10, "TenDuplicate");
		ASSERT_FALSE(inserted);
		ASSERT_EQ(2, m_sb.m_dataMap.size());
		ASSERT_EQ("Twenty", m_sb.m_dataMap.at(20));
	}

	TEST_F(StructuredBindingTest, GetLabelFromStruct_CorrectlyBinds)
	{
		std::string label = m_sb.getLabelFromStruct(5, 10, "Home");
		ASSERT_EQ("Home", label);
	}

	TEST_F(StructuredBindingTest, ProcessTuple_CorrectlyExtractsAndCombines)
	{
		std::tuple<std::string, int> data{ "Age", 35 };
		std::string result = m_sb.procssTuple(data);
		ASSERT_EQ("Age,35", result);
	}
}