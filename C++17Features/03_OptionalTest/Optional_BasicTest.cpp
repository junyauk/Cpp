#include "pch.h"
#include "gtest/gtest.h"
#include "..\03_Optional\Optional_Basic.h"

namespace OptionalTest
{
    class OptionalTest : public ::testing::Test
    {
    protected:
        OPTIONAL_Basic::Optional_Basic m_ob;

        void SetUp() override
        {
            // Ensure m_ob is in a known state
//            m_ob.clear();
            // Re-initialize map state if necessary, but we'll mostly rely on the ctor.
        }

        void TearDown() override
        {
            // Cleanup after each test
        }
    };

    // Test Case 1: findValue - Key Found
    TEST_F(OptionalTest, FindValue_Found)
    {
        // Key "Bob" is expected to be found
        auto result = m_ob.findValue("Bob");
        // Check using has_value()
        ASSERT_TRUE(result.has_value());
        // Check the value
        ASSERT_EQ(202, *result);
    }

    // Test Case 1: findValue - Key Not Found
    TEST_F(OptionalTest, FindValue_NotFound)
    {
        // Key "David" is not expected to be found
        auto result = m_ob.findValue("David");
        // Check using operator bool()
        ASSERT_FALSE(result);
        // The optional should be disengaged
        ASSERT_FALSE(result.has_value());
    }

    // Test Case 1: Accessing a disengaged optional should throw std::bad_optional_access
    TEST_F(OptionalTest, AccessDisengaged_ThrowsException)
    {
        // Disengaged optional
        auto result = m_ob.findValue("Zoe");
        // Accessing the value() method on a disengaged optional throws
        ASSERT_THROW(result.value(), std::bad_optional_access);
    }

    // Test Case 2: Value Or - Value Present
    TEST_F(OptionalTest, GetValueOrDefault_Present)
    {
        // Value for "Alice" is 101, default is 999
        auto result = m_ob.getValueOrDefault("Alice", 999);
        ASSERT_EQ(101, result);
    }

    // Test Case 2: Value Or - Value Absent, returns default
    TEST_F(OptionalTest, GetValueOrDefault_Absent)
    {
        // Value for "Zoe" is absent, default is 999
        auto result = m_ob.getValueOrDefault("Zoe", 999);
        ASSERT_EQ(999, result);
    }

    // Test Case 4: Member Access and Check - ID Set and Matches
    TEST_F(OptionalTest, IsPendingId_SetAndMatches)
    {
        m_ob.setPendingId(500);
        ASSERT_TRUE(m_ob.isPendingId(500));
    }

    // Test Case 4: Member Access and Check - ID Set but No Match
    TEST_F(OptionalTest, IsPendingId_SetButNoMatch)
    {
        m_ob.setPendingId(500);
        ASSERT_FALSE(m_ob.isPendingId(600));
    }

    // Test Case 4: Member Access and Check - ID Not Set (Disengaged)
    TEST_F(OptionalTest, IsPendingId_NotSet)
    {
        // m_pendingId is std::nullopt
        m_ob.setPendingId(std::nullopt);
        ASSERT_FALSE(m_ob.isPendingId(500));
    }
}
