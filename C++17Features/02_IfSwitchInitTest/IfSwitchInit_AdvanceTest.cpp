#include "pch.h"
#include "gtest/gtest.h"
#include "..\02_IfSwitchInit\IfSwitchInit_Advance.h"
#include <string>
#include <mutex>

namespace IfSwitchInitializerAdvanceTest
{
    class InitializerAdvanceTest : public ::testing::Test
    {
    protected:
        IFSWITCHINITIALIZER_Advance::Initializer_Advance m_adv;
    };

    // Test Case 1: RAII Lock Management
    TEST_F(InitializerAdvanceTest, LockManagement_HeldInIfBlock)
    {
        // Case 1: needsLocking is true. The lock is created and its RAII property is active.
        auto result_locked = m_adv.processWithLock(true);
        ASSERT_EQ("Locked processing done by: MyLock", result_locked);
    }

    // Test Case 1b: Lock Management (Checking the else block access)
    TEST_F(InitializerAdvanceTest, LockManagement_AccessInElseBlock)
    {
        // Case 2: needsLocking is false. The lock is still created (initializer runs first).
        // The control flow enters 'else', but 'lock' is still guaranteed to be in scope
        // until the end of the entire if/else construct.
        auto result_unlocked = m_adv.processWithLock(false);
        // The SimpleLock destructor runs *after* the else block, so it should report 'Locked'
        // based on the code's logic, demonstrating its extended scope.
        ASSERT_NE(std::string::npos, result_unlocked.find("Skipped locking. Lock name: MyLock"));
    }
    // Test Case 2: Lifetime management for optional return values (Success)
    TEST_F(InitializerAdvanceTest, ResourceProcessing_SuccessAndLifetime)
    {
        // ID > 0 should return a resource. Value should be ID * 10 (100)
        std::string result = m_adv.checkAndProcessResource(10);
        ASSERT_EQ("Resource processed. Value: 100", result);
    }

    // Test Case 2b: Lifetime management (Failure)
    TEST_F(InitializerAdvanceTest, ResourceProcessing_FailureAndLifetime)
    {
        // ID <= 0 should return nullopt. The 'result' variable is still accessible in the else block.
        std::string result = m_adv.checkAndProcessResource(0);
        ASSERT_EQ("Resource not found for ID: 0", result);
    }

    // Test Case 3: Complex initialization in a switch statement
    TEST_F(InitializerAdvanceTest, SwitchInitializer_CorrectCase)
    {
        // Input 7: 7 % 3 = 1 -> Case 1
        ASSERT_EQ("Case One (Input % 3 = 1)", m_adv.checkStatusValue(7));

        // Input 6: 6 % 3 = 0 -> Case 0
        ASSERT_EQ("Case Zero (Input % 3 = 0)", m_adv.checkStatusValue(6));

        // Input 8: 8 % 3 = 2 -> Default
        ASSERT_EQ("Case Default (Input % 3 = 2)", m_adv.checkStatusValue(8));
    }
}


