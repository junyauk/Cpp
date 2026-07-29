#include "pch.h"
#include "gtest/gtest.h"
#include "..\00_Concepts\Concepts_Basic.h"

using Concepts_Basic::ConceptsBasic;

namespace Concepts_Basic_Test
{
    // Test fixture for ConceptsBasic
    class ConceptsBasicTest : public ::testing::Test
    {
    protected:
        ConceptsBasic m_conceptsBasic;

        // Custom struct that satisfies the CompareLessGreater concept
        struct MyStruct
        {
            int m_value;
            bool operator<(const MyStruct& other) const { return m_value < other.m_value; }
            bool operator>(const MyStruct& other) const { return m_value > other.m_value; }
            bool operator=(const MyStruct& other) const { return m_value == other.m_value; }
        };

        // Custom struct that ONLY satisfies std::equality_comparable
        struct MyEqualOnly
        {
            int m_value;
            bool operator==(const MyEqualOnly& other) const { return m_value == other.m_value; }
        };
    };

    // Test case for isGreaterThan with int (satisfies CompareLessGreater)
    TEST_F(ConceptsBasicTest, IsGreaterThan_Int)
    {
        EXPECT_TRUE(m_conceptsBasic.isGreaterThan(5, 3));
        EXPECT_FALSE(m_conceptsBasic.isGreaterThan(1, 10));
    }

    // Test case for isGreaterThan with MyStruct (satisfies CompareLessGreater)
    TEST_F(ConceptsBasicTest, IsGreaterThan_CustomStruct)
    {
        MyStruct a{ 100 }, b{ 50 };
        EXPECT_TRUE(m_conceptsBasic.isGreaterThan(a, b));
        EXPECT_FALSE(m_conceptsBasic.isGreaterThan(b, a));
    }

    // Test case for areEqual with string (satisfies std::equality_comparable)
    TEST_F(ConceptsBasicTest, AreEqual_String)
    {
        std::string s1 = "hello";
        std::string s2 = "hello";
        std::string s3 = "world";
        EXPECT_TRUE(m_conceptsBasic.areEqual(s1, s2));
        EXPECT_FALSE(m_conceptsBasic.areEqual(s1, s3));
    }

    // Test case for areEqual with MyEqualOnly (satisfies std::equality_comparable)
    TEST_F(ConceptsBasicTest, AreEqual_MyEqualOnly)
    {
        MyEqualOnly a{ 1 }, b{ 1 };
        MyEqualOnly c{ 2 };
        EXPECT_TRUE(m_conceptsBasic.areEqual(a, b));
        EXPECT_FALSE(m_conceptsBasic.areEqual(a, c));

        // NOTE: If you uncomment the line below, it will cause a compilation error
        // because MyEqualOnly does not satisfy CompareLessGreater. 
        // This is the compile-time check provided by Concepts.
        // EXPECT_TRUE(m_conceptsBasic.isGreaterThan(a, c)); 
    }

    // Test case for isContainerEmpty with vector (satisfies requires clause)
    TEST_F(ConceptsBasicTest, IsContainerEmpty_Vector)
    {
        std::vector<int> emptyVec;
        std::vector<int> filledVec = { 1,2,3 };
        EXPECT_TRUE(m_conceptsBasic.isContainerEmpty(emptyVec));
        EXPECT_FALSE(m_conceptsBasic.isContainerEmpty(filledVec));
    }

    // Test case for getTypeInfo demonstrating overload resolution
    TEST_F(ConceptsBasicTest, OverloadResolution_TypeInfo)
    {
        // std::integral constrained version is chosen
        EXPECT_EQ("Integral Type", m_conceptsBasic.getTypeInfo(5));
        // std::floating_point constrained version is chosen
        EXPECT_EQ("Floating Point Type", m_conceptsBasic.getTypeInfo(5.5f));
        // General unconstrained version is chosen
        EXPECT_EQ("Other Type", m_conceptsBasic.getTypeInfo("text"));
    }

}

